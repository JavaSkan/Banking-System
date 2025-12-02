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

function CustLogin(){
    let AccNum=document.getElementById("customer_account_number").value;
    let password=document.getElementById("password").value;
    CustLoginCPP(AccNum+"*"+password).then((answer)=>{
        if(answer=="false"){
            alert("moch mawjoud");
        }else if(answer=="falseP"){
            alert("mdp ghlt");
        }else{
            goToPage('CustomerInterface.html');
        }
    });
}