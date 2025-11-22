// Read value from C++ and display it
function readFromCpp() {
    getCppMessage("").then(msg => {
        document.getElementById('result').innerText = msg;
    }).catch(err => console.error("Error reading from C++:", err));
}

// Send value to C++ and display reply
function sendToCpp() {
    const val = document.getElementById('userInput').value;

    sendToCppFunc(val).then(reply => {
        // reply is already a JSON string, so use JSON.parse
        try {
            const parsed = JSON.parse(reply);
            document.getElementById('response').innerText = parsed;
        } catch (e) {
            console.error("Failed to parse C++ reply:", e, reply);
            document.getElementById('response').innerText = reply; // fallback
        }
    }).catch(err => console.error("Error sending to C++:", err));
}
