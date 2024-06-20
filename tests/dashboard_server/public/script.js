const socket = io();
let selectedElement = null;
let selectedPlayer = null;
let selectedTeam = null;
let responseTimes = [];
let ramUsage = [];
let cpuUsage = [];

// Maximum number of data points to display on the charts
const MAX_DATA_POINTS = 20;

function showSection(sectionId) {
    const sections = document.querySelectorAll('.section');
    sections.forEach(section => {
        section.classList.remove('active');
    });
    document.getElementById(sectionId).classList.add('active');
}

function connectToServer() {
    const hostname = document.getElementById('hostname').value;
    const port = document.getElementById('port').value;
    if (hostname && port) {
        socket.emit('connect_to_server', { hostname, port });
        socket.emit('send_message', { message: 'DASHBOARD\n', timestamp: Date.now() });
    } else {
        showPopup('error', 'Please enter both IP address and port.');
    }
}

function showPopup(status, message) {
    const popup = document.getElementById('popup');
    const popupMessage = document.getElementById('popup-message');
    popupMessage.textContent = message;
    popup.classList.remove('success', 'error');
    popup.classList.add(status);
    popup.style.display = 'block';
}

function closePopup() {
    document.getElementById('popup').style.display = 'none';
}

socket.on('connection_status', (data) => {
    if (data.status === 'success') {
        showPopup('success', data.message);
        showSection('map');
    } else {
        showPopup('error', data.message);
    }
});

socket.on('server_response', (data) => {
    const response = JSON.parse(data.response);
    const responseTime = Date.now() - data.timestamp;

    // Manage response times array
    responseTimes.push(responseTime);
    if (responseTimes.length > MAX_DATA_POINTS) responseTimes.shift();

    // Manage RAM usage array
    ramUsage.push(response.utils.ram_usage);
    if (ramUsage.length > MAX_DATA_POINTS) ramUsage.shift();

    // Manage CPU usage array
    cpuUsage.push(response.utils.cpu_usage);
    if (cpuUsage.length > MAX_DATA_POINTS) cpuUsage.shift();

    updateDashboard(response);
    updateCharts();
});

function updateDashboard(data) {
    updateMap(data.map);
    updatePlayers(data.players);
    updateTeams(data.teams);
    updateUtils(data.utils);

    if (selectedElement) {
        showElementDetails(selectedElement);
    }
    if (selectedPlayer) {
        showPlayerDetails(selectedPlayer);
    }
    if (selectedTeam) {
        showTeamDetails(selectedTeam);
    }
}

function updateMap(map) {
    const mapTable = document.getElementById('map-table');
    mapTable.innerHTML = '';

    const headerRow = document.createElement('tr');
    const emptyHeader = document.createElement('th');
    headerRow.appendChild(emptyHeader);
    for (let x = 0; x < map[0].length; x++) {
        const headerCell = document.createElement('th');
        headerCell.textContent = x;
        headerRow.appendChild(headerCell);
    }
    mapTable.appendChild(headerRow);

    map.forEach((row, rowIndex) => {
        const tableRow = document.createElement('tr');
        const rowHeader = document.createElement('th');
        rowHeader.textContent = rowIndex;
        tableRow.appendChild(rowHeader);

        row.forEach((cell, cellIndex) => {
            const cellElement = document.createElement('td');
            cellElement.textContent = `(${rowIndex}, ${cellIndex})`;
            cellElement.addEventListener('click', () => {
                selectedElement = cell;
                showElementDetails(cell);
            });
            tableRow.appendChild(cellElement);
        });

        mapTable.appendChild(tableRow);
    });

    if (selectedElement) {
        showElementDetails(selectedElement);
    }
}

function showElementDetails(element) {
    if (!element) return;
    const elementDetails = document.getElementById('element-details');
    elementDetails.innerHTML = `
        <p>Food: ${element.food}</p>
        <p>Linemate: ${element.linemate}</p>
        <p>Deraumere: ${element.deraumere}</p>
        <p>Sibur: ${element.sibur}</p>
        <p>Mendiane: ${element.mendiane}</p>
        <p>Phiras: ${element.phiras}</p>
        <p>Thystame: ${element.thystame}</p>
    `;
}

function updatePlayers(players) {
    const playerList = document.getElementById('player-list');
    playerList.innerHTML = '';
    players.forEach(player => {
        const playerDiv = document.createElement('div');
        playerDiv.textContent = `Player ${player.id_player}`;
        playerDiv.className = 'player-item';
        playerDiv.addEventListener('click', () => {
            selectedPlayer = player;
            showPlayerDetails(player);
        });
        playerList.appendChild(playerDiv);
    });

    if (selectedPlayer) {
        showPlayerDetails(selectedPlayer);
    }
}

function showPlayerDetails(player) {
    if (!player) return;
    const playerDetails = document.getElementById('player-details');
    playerDetails.innerHTML = `
        <p>ID: ${player.id_player}</p>
        <p>Food: ${player.food}</p>
        <p>Linemate: ${player.linemate}</p>
        <p>Deraumere: ${player.deraumere}</p>
        <p>Sibur: ${player.sibur}</p>
        <p>Mendiane: ${player.mendiane}</p>
        <p>Phiras: ${player.phiras}</p>
        <p>Thystame: ${player.thystame}</p>
        <p>Level: ${player.level_player}</p>
        <p>Direction: ${player.view_direction}</p>
        <p>Position: (${player.x}, ${player.y})</p>
    `;
}

function updateTeams(teams) {
    const teamList = document.getElementById('team-list');
    teamList.innerHTML = '';
    teams.forEach(team => {
        const teamDiv = document.createElement('div');
        teamDiv.textContent = `Team ${team.name}`;
        teamDiv.className = 'team-item';
        teamDiv.addEventListener('click', () => {
            selectedTeam = team;
            showTeamDetails(team);
        });
        teamList.appendChild(teamDiv);
    });

    if (selectedTeam) {
        showTeamDetails(selectedTeam);
    }
}

function showTeamDetails(team) {
    if (!team) return;
    const teamDetails = document.getElementById('team-details');
    teamDetails.innerHTML = `
        <p>Name: ${team.name}</p>
        <p>ID: ${team.team_id}</p>
        <p>Players: ${team.players_id.join(', ')}</p>
    `;
}

function updateUtils(utils) {
    const utilsLeft = document.getElementById('utils-left');
    utilsLeft.innerHTML = '';

    const utilsData = [
        { label: 'Port', value: utils.port !== undefined ? utils.port : "N/A" },
        { label: 'Map Width', value: utils.map_width !== undefined ? utils.map_width : "N/A" },
        { label: 'Map Height', value: utils.map_height !== undefined ? utils.map_height : "N/A" },
        { label: 'Client Number', value: utils.client_nb !== undefined ? utils.client_nb : "N/A" },
        { label: 'Time', value: utils.time !== undefined ? utils.time : "N/A" },
        { label: 'fd_gui', value: utils.fd_gui !== undefined ? utils.fd_gui : "N/A" },
        { label: 'fd_web_debug', value: utils.fd_web_debug !== undefined ? utils.fd_web_debug : "N/A" },
        { label: 'Object', value: utils.obj !== undefined ? utils.obj : "N/A" },
        { label: 'Stop Server', value: utils.stop_server !== undefined ? utils.stop_server : "N/A" },
        { label: 'Start Game', value: utils.start_game !== undefined ? utils.start_game : "N/A" },
        { label: 'Look String', value: utils.look_str !== undefined ? utils.look_str : "N/A" },
        { label: 'RAM Usage', value: utils.ram_usage !== undefined ? utils.ram_usage : "N/A" },
        { label: 'CPU Usage', value: utils.cpu_usage !== undefined ? utils.cpu_usage : "N/A" }
    ];

    utilsData.forEach(data => {
        const row = document.createElement('div');
        row.className = 'utils-row';
        row.innerHTML = `<span>${data.label}:</span> <span>${data.value}</span>`;
        utilsLeft.appendChild(row);
    });
}

function changeFrequency() {
    const frequencyInput = document.getElementById('frequency-input').value;
    if (frequencyInput && frequencyInput >= 0) {
        socket.emit('send_message', { message: `sst ${frequencyInput}\n`, timestamp: Date.now() });
    } else {
        showPopup('error', 'Please enter a valid non-negative frequency.');
    }
}

function updateCharts() {
    updateChart(responseTimes, 'responseTimeChart', 'Response Time (ms)');
    updateChart(ramUsage, 'ramUsageChart', 'RAM Usage (%)');
    updateChart(cpuUsage, 'cpuUsageChart', 'CPU Usage (%)');
}

function updateChart(dataArray, chartId, label) {
    const layout = {
        title: {
            text: label,
            font: {
                color: '#e0e0e0'
            }
        },
        paper_bgcolor: '#2c2c2c',
        plot_bgcolor: '#2c2c2c',
        xaxis: {
            title: 'Time',
            showgrid: false,
            zeroline: false,
            color: '#e0e0e0'
        },
        yaxis: {
            title: label,
            showline: false,
            color: '#e0e0e0'
        },
        margin: {
            l: 40, r: 40, t: 40, b: 40
        },
        width: document.querySelector('.chart-container').clientWidth / 3 - 20,
        height: 200,
    };

    const trace = {
        x: Array.from({ length: dataArray.length }, (_, i) => i + 1),
        y: dataArray,
        type: 'scatter',
        line: { color: '#00FF00' }
    };

    Plotly.newPlot(chartId, [trace], layout);
}

function refreshData() {
    socket.emit('send_message', { message: 'DASHBOARD\n', timestamp: Date.now() });
}

function toggleMode() {
    const body = document.body;
    body.classList.toggle('dark-mode');
    body.classList.toggle('light-mode');

    const modeBtn = document.getElementById('toggle-theme');
    if (body.classList.contains('dark-mode')) {
        modeBtn.textContent = 'Light Mode';
    } else {
        modeBtn.textContent = 'Dark Mode';
    }

    // Update charts to match the new mode
    updateCharts();
}
