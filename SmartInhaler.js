/* Open when span element is clicked */
function openNav()
{
    document.getElementById("testNav").style.height = "100%";
}

/* Close when button is clicked */
function closeNav()
{
    document.getElementById("testNav").style.height = "0%";
}

// FetchAPI testing //
function updateTemperature()
{
    fetch('/getTemperature')
    .then(response => response.json()) // JSON response
    .then(data =>
    {
        document.getElementById("TempValue").innerText = data.temperature + " C";
    
    })
    .catch(error => 
    {
        console.error("Error fetching temperature", error);
    });
}

// Update the temperature every 2 seconds
setInterval(updateTemperature, 2000);
// Call updateTemperature intially to display the value straight away
window.onload = updateTemperature;

function updateHumidity()
{
    fetch('/getHumidity')
    .then(response => response.json()) // JSON response
    .then(data =>
    {
        document.getElementById("HumidityValue").innerText = data.humdity + " %";
    
    })
    .catch(error => 
    {
        console.error("Error fetching humidity", error);
    });
}

setInterval(updateHumidity, 2000);
window.onload = updateHumidity;


function updateDust()
{
    fetch('/getDust')
    .then(response => response.json()) // JSON response
    .then(data =>
    {
        document.getElementById("DustValue").innerText = data.dust + " ug/m3";
    
    })
    .catch(error => 
    {
        console.error("Error fetching dust levels", error);
    });
}

setInterval(updateDust, 2000);
window.onload = updateDust;



function updatePollen()
{
    fetch('/getPollen')
    .then(response => response.json()) // process response into JSON 
    .then(data => // Handle the data
    {
        document.getElementById("PollenValue").innerText = data.updatePollen + " ug/m3";
    
    })
    .catch(error =>  // Handle the error
    {
        console.error("Error fetching pollen levels", error);
    });
}

setInterval(updatePollen, 2000);
window.onload = updatePollen;