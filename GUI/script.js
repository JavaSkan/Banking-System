// Read value from C++ and display it
function readFromCpp(id) {
    getCppObj("").then(msg => {
        document.getElementById(id).innerText = msg;
    }).catch(err => console.error("Error reading from C++:", err));
}

// Send value to C++ and display reply
function sendToCpp(id) {
    const val = document.getElementById(id).value;
    sendToCppFunc(val).then(reply => {
        // reply is plain text, so display it directly
        document.getElementById('response').innerText = reply;
    }).catch(err => console.error("Error sending to C++:", err));
}
