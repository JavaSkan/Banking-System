function AddEmpl(){
    let ID=document.getElementById("IDInput").value;
    let name=document.getElementById("nameInput").value;
    let last=document.getElementById("lastnameInput").value;
    let address=document.getElementById("adressInput").value;
    let salary=document.getElementById("salaryInput").value;

    info=ID+"*"+name+"*"+last+"*"+address+"*"+salary;
    sendRegEmplInfo(info).then((answer)=>{
        console.log(answer);
    })
}

function EmplLogin(){
    let ID=document.getElementById("employee_ID").value;
    let password=document.getElementById("password").value;
    EmplLoginCPP(ID+"*"+password).then((answer)=>{
        if(answer=="false"){
            alert("moch mawjoud");
        }else if(answer=="falseP"){
            alert("mdp ghlt");
        }else{
            goToPage('EmployeeInterface.html');
        }
    });
}