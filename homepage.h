String smartInhalerHomepage = F(R"=====(
  
  
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="icon" type="image/x-icon" href="JDlogo1.png">
    <title>Smart Inhaler</title>
    <style>
    /* General Styles */
* 
{
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body 
{
    font-family: Arial;
    background-color: white;
}
#NavBar
{
    display: flex;
    position: sticky;
    top: 0;
    overflow: hidden;
    background-color: black;
}
#NavBar a
{
    top: 20px;
    left: 50px;
    display: flex;
    padding: 14px;
    text-decoration: none;
    color: white;
    font-size: 20px;
}
#MenuButton
{
    top:50px;
    right:500px;
    color: white;
    display: flex;
    font-size: 20px;
}
/* Welcome Section */
.welcome 
{
    background-image:url("I3.jpg");
    width: auto;
    height: 1000px;
    padding: 100px 20px;
    text-align: center;
    justify-content: center;
    align-items: center;
    margin-bottom: 50px;
}

.welcome h1 
{
    margin-top: 250px;
    font-size: 48px;
    margin-bottom: 20px;
}

.welcome p 
{
    font-size: 20px;
    margin-bottom: 30px;
}




.overlay /* For background */
{
    /* Can change heigth and width */ 
    height: 0%;
    width: 100%;
    position: fixed;
    z-index: 1; /* Sit on the top of the webpage */
    left:0;
    top:0;
    background-color: rgb(0,0,0); /* transparent black fallback colour */
    background-color: rgba(0,0,0,0.9); /* Black with opacity */
    overflow-y: hidden; /* Disable horizontal scroll */
    transition: 0.5s; /* transition time for slide effect */
}

#overlay-content /* Positioning content inside the overlay */
{
    position: absolute;
    top:25%; /* 25% drop the top */
    width:100%;
    align-items: center;
    text-align: center;
    margin-top: 30px; /* To avouid conflict with the close button on smaller screens */
}

.overlay a
{
    padding: 8px;
    text-decoration: none;
    font-size: 36px;
    color: #818181;
    display: block;
    transition :0.3s;
}

/* For colour change when hovering over links */
.overlay a:hover, .overlay a:focus
{
    color: whitesmoke;
}

/* Position close button in top right */
.overlay .closebtn
{
    position: absolute;
    top:20px;
    right:45px;
    font-size: 60px;
}

/* To avoid overlapping on smaller screens */
@media screen and (max-height:450px)
{
    .overlay {overflow-y: auto;}
    .overlay a {font-size: 20px}
    .overlay .closebtn
     {
    font-size: 40px;
    top: 15px;
    right: 35px;
    }
}

/* About Section */
.description
{
    display: flex;
    text-align: center;
    align-items: center;
    justify-content: center;
    font-size: 25px;
    margin-top: 25px;
}
.description h
{
    font-size: 32px;
    margin-bottom: 20px;
    text-align: center;
}
.description p
{
    font-size: 24px;
    margin-top: 20px;
    width: 500px;

}
.description > img
{
    border-radius: 10px;
    display: flex;
    width: 300px;
    height: 300px;
    margin-bottom: 60px;
}

.flex-container1
{
    margin-top: 100px;
    border-radius: 10px;
    display: flex;
    text-align: center;
    font-size: 24px;
    flex-direction: row;
    margin-bottom: 10px;
}

.flex-container1 > div img /* CSS for image styling*/
{
    border-radius: 10px;
    display: flex;
    width: 300px;
    height: 300px;
}

.flex-container1 > div /* CSS for styling of box*/
{ 
    background-color: rgb(250,250,250);
    border: 1px ;
    border-radius: 10px;
    flex:1;
    font-size: 24px;
    line-height: 40px;
    margin: 10px;
    padding: 16px;
    width: 60px;
} 

.flex-container1 > div h
{
    font-size: 32px;
    margin-bottom: 20px;
    text-align: center;
}

h1
{
    text-align: center;
    font-size: 32px;
    margin-bottom: 20px;
    margin-top: 20px;
}


/* Video */
#video
{
    font-size: 32px;
    max-width: 600px;
    margin: auto;    
    text-align: center;
}

.flex-container2
{
    background-color: white;
    border-radius: 10px;
    display: flex;
    margin-bottom: 10px;
}

.flex-container2 > div
{
    background-color: rgb(250, 250, 250); /* Slightly darker white background for flexbox boxes to create hovering affect*/
    border: 1px;
    border-radius: 10px;
    flex:1;
    font-size: 24px;
    line-height: 40px;
    margin: 10px;
    padding: 16px;
    width: 60px;
} 

.flex-container2 > div h
{
    font-size: 32px;
    margin-bottom: 20px;
    text-align: center;
}

/* ThingSpeak Charts */
.dust
{
    display: flex;
    flex-direction: row;
    justify-content: center; 
}
.pollen
{
    display: flex;
    flex-direction: row;
    justify-content: center;
}
.temperature
{
    display: flex;
    flex-direction: row;
    justify-content: center;
}
.humidity
{
    
    display: flex;
    flex-direction: row;
    justify-content: center;
}
h2
{
    margin-top: 50px;
    display: flex;
    justify-content: center;
}
/* Footer */
footer 
{
    background-color: white;
    color: black;
    text-align: center;
    padding: 20px;
    font-size: 14px;
}
</style>
</head>
<body>

<!-- Navigation Bar -->
<div id="NavBar">
        <a href=SmartInhaler.html><b>JD</b></a>
  
    <div id="MenuButton">
            <span style="cursor: pointer;" onclick="openNav()">&#9776;</span>
    </div>
</div>

<header>
<nav>
<!-- W3schools menu testing -->

<div id="testNav" class="overlay">
<!--Button to close the overlway navigation-->
<a href="javascript:void(0)" class="closebtn" onclick="closeNav()">&times;</a>

<!--overlay content-->
    <div id="overlay-content">
        <a href="#about">About</a>
        <a href="#Charts">Charts</a>
        <a href="#video">My IoT Video</a>
        <a href="#further-info">Further Information</a>
    </div>
</div>
</nav>
</header>

<!-- Welcome Section -->

<section class="welcome">
    
    <h1>Welcome to Smart Inhaler</h1>
    <p>Asthma management made simple.</p>

    
</section>

<!-- About Section -->
 <section id="about">
    
<div class="description">
    <div>
        <h><b>How does SmartInhaler work?</b></h>
        <br>
        <p>I use multiple sensors to constantly measure enviornmental readings to help you understand and manage your asthma. 
            When a reading goes too high, it will display the reading on the OLED screen, the buzzer will also go off, alerting users of the high recorded
            reading.
            My IoT device 
            aim to battle asthma by bringing down the risk of asthma influenced death. 
        </p>
    </div>
</div>


    <div class="flex-container1">
        <div>
            <h><b>Buzzer goes off</b></h>
            <p>The buzzer will alert users when live readings of dust, temperature and pollen levels in your current location reach an unsafe level.
            </p>
        </div>

        <div>
        <h><b>Reading Recieved</b></h>
        <p>As well as this, the OLED screen will show current live readings of dust, temperature and pollen levels in your current location, this will notify users
            of when it is reccomended to take a puff from their inhaler.
        </p>
        </div>

        <div>
        <h><b>Breathe Easier</b></h>
        <p>After reading the live readings from our device, take your inhaler to prevent any discomfort in the chest/
        breathing. 
        </p>
        </div>
    </div>
</section>
<!-- Video Section -->
 <section id="video">
    <h><b>My IoT Video</b></h>
    <video width="600" height="450" controls>
    <source src="iotvideo.mp4">
    </video>
 </section>

<!-- Further Information Section Using Flexbox-->
 <section id="further-info">
    <h1>Further Details</h1>
    <div class="flex-container2">
    
        <div>
            <h><b>What sensors did I use?</b></h>
            <p>GP2Y1014AU - Dust Sensor
                <br>
                DHT11 - Temperature Sensor
                <br>
                SN-GCJA5 - Pollen Sensor
            </p>
        </div>


        <div>
            <h><b>Enviornmental hazard detection</b></h>
            <p>The sensors detect dangerous pollen and dust levels that could potentially bring on sudden atshma attacks.By tracking PM 2.5 and 1.0 levels my device 
                alert you before issues arise.</p>
        </div>

        <div>
            <h><b>Live Readings</b></h>
            <p>My website constantly updates the live enviornmental readings from the sensors
                by displaying readings on the web server. Never worry about atshma readings again as the 
                constant refreshing webpage keeps you updated.
            </p>
        </div>
    </div>
</section>
</header>


<!-- ThingSpeak Data Test -->
<section id="Charts">
    <h1>Live Enviornmental Readings</h1>

    <h2><u>Understanding Dust Levels</u></h2>
    <div class="dust">   
        <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2767873/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=Dust+Levels&type=line&xaxis=Time&yaxis=Dust+Level+%28PM+2.5%29"></iframe>
    <p>
    <br><br>
     Dust: <span id="dustValue"> Loading...</span>
    <br><br>
    - Good - PM2.5 reading is anything less than 25µg/m3
    <br><br>
    - Moderate - PM2.5 reading is anywhere betwwen 25-50µg/m3
    <br><br>
    - Dangerous - PM2.5 reading is anywhere from 50-300µg/m3
    </p>
    </div>

    <h2><u>Understanding Pollen Levels</u></h2>
    <div class="pollen">
    <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2767873/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=Pollen+Levels&type=line&xaxis=Time&yaxis=Pollen+Levels%28grains%2Fm%C2%B3%29"></iframe>
    <p>
    <br><br>
    Pollen: <span id="pollenValue"> Loading...</span>
    <br><br>
    -Good - 0-14 grain/m3, this results in minimal allergic symtpoms
    <br><br>
    - Moderate - 5-89 grain/m3, this results in mild symptoms (i.e sneezing, wheezing)
    <br><br>
    - Dangerous - 200-1,500+ grain/m3, this results in dangerous symptoms (i.e swelling of throat, chest pain)
    </p>
    </div>
    
    <h2><u>Understanding Temperature Levels</u></h2>
    <div class="temperature">
        <iframe width="460" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2767873/widgets/1069547"></iframe>
        <p>
            <br><br>
            Temperature: <span id="tempValue"> Loading...</span>
            <br><br>
            - Dangerous (Cold) - Anything below 10°C, this can cause airway constriction.
            <br><br>
            - Ideal - Anything between 20-22°C is considered good ventilation. 
            <br><br>
            - Dangerous (Hot) - Anything above 27°C with high humidity, this increases airway inflamation.
        </p>    
       
    </div>

    <h2><u>Understanding Humidity Levels</u></h2>
    <div class="humidity">
    <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2767873/widgets/1069549"></iframe>
    <p>
        <br><br>
        Humidity: <span id="humidityValue"> Loading...</span>
        <br><br>
        - Good - 40-50%, this results in comfortable breathing
        <br><br>
        - Moderate - 30-40%, this can result in mild irritation (i.e dry throat, cough, dried airways)
        <br> <br>
        - Dangerous - 0-20% or 70%+, this can cause asthma flare ups (i.e difficulty breathing, increased mucus buildup, wheezing)
        <br><br>
    </p>
    </div>
</section>
</div>
</section>

<!-- Footer -->
<footer>
    <p> 2025 SmartInhaler | JD</p>
</footer>

<script>
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
function updateTemperature() {
      fetch('/getTemperature')
        .then(response => response.json())
        .then(data => {
          document.getElementById("tempValue").innerText = data.temperature + " C";
        })
        .catch(error => {
          console.error("Error fetching temperature", error);
        });
    }

    setInterval(updateTemperature, 2000);
    updateTemperature();

    function updateHumidity() {
      fetch('/getHumidity')
        .then(response => response.json())
        .then(data => {
          document.getElementById("humidValue").innerText = data.humidity + " %";
        })
        .catch(error => {
          console.error("Error fetching humidity", error);
        });
    }

    setInterval(updateHumidity, 2000);
    updateHumidity();


        function updatePollen() {
      fetch('/getPollen')
        .then(response => response.json())
        .then(data => {
          document.getElementById("pollenValue").innerText = data.pollen + " ug/m3";
        })
        .catch(error => {
          console.error("Error fetching pollen", error);
        });
    }

    setInterval(updatePollen, 2000);
    updatePollen();

      function updateDust() {
      fetch('/getDust')
        .then(response => response.json())
        .then(data => {
          document.getElementById("dustValue").innerText = data.dust + " ug/m3";
        })
        .catch(error => {
          console.error("Error fetching dust", error);
        });
    }

    setInterval(updateDust, 2000);
    updateDust();
</script>
</body>
</html>

</html>)=====");