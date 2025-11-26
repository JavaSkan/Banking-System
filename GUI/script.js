// auto sends date to cpp 
let date=new Date;
let day=date.getDate();
let month=date.getMonth()+1;
let year=date.getFullYear();
window.sendDate(day+"*"+month+"&"+year).then((r)=>{
    console.log(
        "CPP replied: " + r);
});

//ntesti beha
function readFromCpp(id) {
    getCppObj("")
        .then(msg => {
            document.getElementById(id).innerText = msg;
        })
        .catch(err => console.error("Error reading from C++:", err));
}

//tsakarli el webview
function closeWin() {
    closeWindow();
}

// Load branch info from C++
function BranchInfo() {
    getInfo()
        .then(info => {
            const [branchName, ID,todaysDate] = info.data.split("*");
            document.getElementById('date').innerText = "Date: " + todaysDate;
            document.getElementById('branch_name').innerText = "Branch: " + branchName;
            document.getElementById('branch_code').innerText = "Code: " + ID;
        })
        .catch(err => console.error("Error getting branch info:", err));
}

// ---- SIMPLE BOOLEAN CHECK FUNCTION (NO ASYNC) ----
//BECH NHEZHA LEL CPP §§§§§§§§§§§§§§§§§§§§§§§§§§§§§ 
/*function checkName() {
    let name=document.getElementById("nameInput");
    let test=true;
    let acc_type = document.getElementById("AccType").value;
    // Trim and remove double spaces
    name = name.trim().replace(/\s+/g, ' ');
    // Empty?
    if (name === "") {
        alert("Name cannot be empty.");
        test= false;
    }
    for (let i = 0; i < name.length; i++) {
        const c = name[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c === ' ')) {
            alert("Name can only contain letters and single spaces.");
            test =false;
        }
    }
    if(test){
        sendRegCusInfo(acc_type+'*'+name);
        console.log("b3athna lel c++")
    }
    return test;
}*/

function sendNow() {
let name = document.getElementById('nameInput').value;
let acc_type = document.getElementById('AccType').value;

window.sendRegCusInfo(acc_type+"*"+name).then((r)=>{
    console.log(
        "CPP replied: " + r);
});

}

function request() {
window.getFromCpp().then((answer)=>{
    alert(
        "CPP says: " + answer);
});
}