const express = require('express');
const path = require('path');
const fs = require('fs');
const cors = require('cors');
const { exec } = require('child_process');

const app = express();
const PORT = 3000;

// Middleware
app.use(cors());
app.use(express.json());
app.use(express.static(__dirname));

// API endpoint to generate route
app.post('/api/generate-route', (req, res) => {
    const { source, destination, mode } = req.body;

    if (!source || !destination || !mode) {
        return res.status(400).json({ 
            status: 'error', 
            message: 'Missing required parameters' 
        });
    }

    const routeFile = path.join(__dirname, 'route.json');
    
    // Delete existing file first
    if (fs.existsSync(routeFile)) {
        fs.unlinkSync(routeFile);
    }



    const command = `"${path.join(__dirname, 'build', 'Debug', 'flight_optimizer.exe')}" ${source} ${destination} ${mode}`;
    console.log(`Executing: ${command}`);

    exec(command, (error, stdout, stderr) => {
        // Special case: No path found (C++ program returns specific exit code)
        if (error?.code === 2) {
            return res.status(404).json({
                status: 'no_route',
                message: 'No flight path exists between these airports'
            });
        }
        
        if (error) {
            console.error(`Error: ${error.message}`);
            return res.status(500).json({
                status: 'error',
                message: 'Route generation failed',
                details: stderr
            });
        }

        setTimeout(() => {
            if (fs.existsSync(routeFile) && fs.statSync(routeFile).size > 0) {
                res.json({ status: 'ok' });
            } else {
                res.status(500).json({
                    status: 'error',
                    message: 'Route file not generated'
                });
            }
        }, 300);
    });
});
// API endpoint to get route data
app.get('/api/route', (req, res) => {
    const routeFile = path.join(__dirname, 'route.json');
    if (fs.existsSync(routeFile)) {
        res.sendFile(routeFile);
    } else {
        res.status(404).json({ 
            status: 'error',
            message: 'Route not found. Generate a route first.' 
        });
    }
});

// Start server
app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});

