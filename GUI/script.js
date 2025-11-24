// Read value from C++ and display it
function readFromCpp(id) {
    getCppObj("")
        .then(msg => {
            document.getElementById(id).innerText = msg;
        })
        .catch(err => console.error("Error reading from C++:", err));
}

function closeWin() {
    closeWindow();
}

// Load branch info from C++
function BranchInfo() {
    getBranchInfo()
        .then(obj => {
            const [branchName, ID] = obj.data.split("*");
            document.getElementById('branch_name').innerText = "Branch: " + branchName;
            document.getElementById('branch_code').innerText = "Code: " + ID;
        })
        .catch(err => console.error("Error getting branch info:", err));
}

// ---- SIMPLE BOOLEAN CHECK FUNCTION (NO ASYNC) ----
function checkName(id) {
    if (typeof getInfo === "function") {
        console.log("walah te5dem exists!");
    } else {
        console.log("la2");
    }    
    let test=true;
    let name = document.getElementById(id).value;
    let acc_type = document.getElementById("AccType").value;

    // Trim and remove double spaces
    name = name.trim().replace(/\s+/g, ' ');

    // Empty?
    if (name === "") {
        alert("Name cannot be empty.");
        return false;
    }

    // Validate characters
    for (let i = 0; i < name.length; i++) {
        const c = name[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c === ' ')) {
            alert("Name can only contain letters and single spaces.");
            test =false;
        }
    }
    console.log("el test mta3 el esm kammel")
    if(test){
        sendNow(name+"*"+acc_type);
        console.log("b3athna lel c++")
    }
    return test;
}

function sendNow() {
let val = document.getElementById('nameInput').value;
window.getInfo(val).then((r)=>{
    alert(
        "CPP replied: " + r);
});
}
function request() {
window.getFromCpp().then((answer)=>{
    alert(
        "CPP says: " + answer);
});
}