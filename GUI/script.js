// Read value from C++ and display it
function readFromCpp(id) {
    getCppObj("").then(msg => {
        document.getElementById(id).innerText = msg;
    }).catch(err => console.error("Error reading from C++:", err));
}

//hedhom el zouz juste njareb behom w khw

// Send value to C++ and display reply
function sendToCpp(id) {
    const val = document.getElementById(id).value;
    sendToCppFunc(val).then(reply => {
        document.getElementById('response').innerText = reply;
    }).catch(err => console.error("Error sending to C++:", err));
}

// Close the WebView window
function closeWin() {
    closeWindow(); //mel c++
}

// Load branch info from C++
function BranchInfo() {
    getBranchInfo().then((obj) => {
        const [branchName,ID] = obj.data.split("*");
        document.getElementById('branch_name').innerText="Branch: "+branchName;
        document.getElementById('branch_code').innerText="Code: "+ID;
    }).catch(err => console.error("Error getting branch info:", err));
}


function checkName(id) {
    let name = document.getElementById(id).value;

    // Remove leading/trailing spaces and replace multiple spaces with a single space
    name = name.trim().replace(/\s+/g, ' ');

    if (name === "") {
        alert("Name cannot be empty.");
        return false;
    }

    for (let i = 0; i < name.length; i++) {
        const c = name[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c === ' ')) {
            alert("Name can only contain letters and single spaces.");
            return false;
        }
    }

    alert("Name is valid!");
    return true;
}

