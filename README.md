# ✈️ Flight Route Optimization System

A system to visualize and optimize flight routes between airports using Dijkstra's algorithm, with interactive mapping.

![{D773510E-94DA-49C6-B690-1531802C720D}](https://github.com/user-attachments/assets/43f294e0-0962-4f3b-9d57-d56300d6f2e7)


![Screenshot 2025-07-06 162506](https://github.com/user-attachments/assets/efd63be0-d857-4376-9a5a-6262798fe96a)

![Screenshot 2025-07-06 180118](https://github.com/user-attachments/assets/db0d66ac-dffe-4e06-8427-cdad072295bc)

![Screenshot 2025-07-06 180332](https://github.com/user-attachments/assets/4e5e07fb-120f-4017-803d-847cc8c0f0f2)


## 🚀 Features
- **Interactive Map**: Visualize flight routes with Leaflet.js
- **Multiple Optimization Modes**:
  - Fastest route (time)
  - Cheapest route (cost) 
  - Fewest stops
- **Airport Lookup**: Search by IATA codes (e.g., JFK, LAX)
- **API Backend**: Node.js/Express server with C++ route calculation

## 🛠️ Tech Stack
| Component       | Technology |
|----------------|------------|
| Frontend       | HTML5, CSS3, JavaScript, Leaflet.js |
| Backend        | Node.js, Express |
| Route Engine   | C++ (Dijkstra's algorithm) |
| Data           | OpenFlights airport/route datasets |

## 📦 Installation

### Prerequisites
- Node.js (v16+)
- C++ compiler (GCC/g++)
- Git

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/flight-route-optimization.git
   cd flight-route-optimization
   ```
2. Install dependencies:
   ```bash
   npm install
   ```
3. Compile C++ program:
   ```bash
   g++ -Iinclude source/*.cpp -o bin/flight_optimizer -static-libgcc -static-libstdc++
   ```
4. Start the server:
   ```bash
   node server.js
   ```
5. Open in browser:  
   `http://localhost:3000`


## 📂 Project Structure
```
project/
├── bin/                 # C++ executable
├── data/                # Airport/route datasets
│   ├── airports.dat
│   └── routes.dat    
│__ index.html           # Frontend files
├── source/              # C++ source code
├── server.js            # Node.js backend
└── package.json
```

## 🤝 Contributing
1. Fork the project
2. Create your branch (`git checkout -b feature/your-feature`)
3. Commit changes (`git commit -m 'Add feature'`)
4. Push (`git push origin feature/your-feature`)
5. Open a Pull Request

## 📄 License
[MIT](https://choosealicense.com/licenses/mit/)

---

*Created with ❤️ by [Vamsi prakash](https://github.com/your-username)*
