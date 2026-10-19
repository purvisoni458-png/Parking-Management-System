
const $ = (id) => document.getElementById(id);

let allVehicles = JSON.parse(localStorage.getItem("parkEaseVehicles") || "[]");

$("todayDate").textContent = new Date().toLocaleDateString("en-GB");

function saveVehicles() {
    localStorage.setItem("parkEaseVehicles", JSON.stringify(allVehicles));
}

function showMessage(id, text, success) {
    const element = $(id);
    element.textContent = text;
    element.style.color = success ? "green" : "crimson";
}

function renderVehicles(list) {
    const tbody = $("vehicleRows");

    if (!list.length) {
        tbody.innerHTML =
            '<tr><td colspan="5" class="empty">No vehicles found.</td></tr>';
    } else {
        tbody.innerHTML = list.map(v => `
            <tr>
                <td>${v.number}</td>
                <td>${v.type}</td>
                <td>#${v.slot}</td>
                <td>${String(v.entryTime).padStart(2, "0")}:00</td>
                <td>Parked</td>
            </tr>
        `).join("");
    }

    $("tableCount").textContent = `Showing ${list.length} vehicles`;
}

function filterVehicles() {
    const query = $("searchInput").value.trim().toUpperCase();
    renderVehicles(allVehicles.filter(v => v.number.includes(query)));
}

function refreshDashboard() {
    $("totalSlots").textContent = 50;
    $("occupiedSlots").textContent = allVehicles.length;
    $("availableSlots").textContent = 50 - allVehicles.length;
    filterVehicles();
}

$("parkForm").addEventListener("submit", function(event) {
    event.preventDefault();

    const number = $("number").value.trim().toUpperCase();
    const type = $("type").value;
    const entryTime = Number($("entryTime").value);

    if (!number) {
        showMessage("parkMessage", "Enter a vehicle number.", false);
        return;
    }
    if (allVehicles.some(v => v.number === number)) {
        showMessage("parkMessage", "This vehicle is already parked.", false);
        return;
    }
    if (allVehicles.length >= 50) {
        showMessage("parkMessage", "Parking is full!", false);
        return;
    }
    if (!Number.isInteger(entryTime) || entryTime < 0 || entryTime > 23) {
        showMessage("parkMessage", "Enter an hour between 0 and 23.", false);
        return;
    }

    const usedSlots = allVehicles.map(v => v.slot);
    let slot = 1;
    while (usedSlots.includes(slot)) slot++;

    allVehicles.push({ number, type, entryTime, slot });
    saveVehicles();
    refreshDashboard();
    showMessage("parkMessage", `Vehicle parked successfully in slot ${slot}!`, true);
    $("parkForm").reset();
});

$("removeForm").addEventListener("submit", function(event) {
    event.preventDefault();

    const number = $("exitNumber").value.trim().toUpperCase();
    const exitTime = Number($("exitTime").value);
    const index = allVehicles.findIndex(v => v.number === number);

    if (index === -1) {
        showMessage("removeMessage", "Vehicle not found.", false);
        return;
    }
    if (!Number.isInteger(exitTime) || exitTime < 0 || exitTime > 23) {
        showMessage("removeMessage", "Enter an exit hour between 0 and 23.", false);
        return;
    }

    const vehicle = allVehicles[index];
    const duration = (exitTime - vehicle.entryTime + 24) % 24;
    const fee = Math.max(1, duration) * 20;

    allVehicles.splice(index, 1);
    saveVehicles();
    refreshDashboard();

    showMessage(
        "removeMessage",
        `Vehicle removed! Duration: ${duration} hour(s). Fee: ₹${fee}`,
        true
    );
    $("removeForm").reset();
});

$("searchInput").addEventListener("input", filterVehicles);

refreshDashboard();
