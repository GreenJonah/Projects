<?php
  session_start();
  require "dbConnect.php";
  $db = get_db();
?>
<html>
<head>
  <title>Project1</title>
  <link rel="stylesheet" type="text/css" href="project1.css">
</head>
<body>

<p id="title">Endurocross 2018 Registration</p>

<form action="insertRacer.php" method="POST">
  <table class="enter">
  <tr> 
    <td>
      <label for="firstName">First Name:</label></br>
      <input class="input" type="text" name="firstName" required>
    </td>
    <td>
      <label for="lastName">Last Name:</label></br>
      <input class="input" type="text" name="lastName" required>
    </td>
  </tr>
  <tr>
    <td>
      <label for="Email">Email:</label></br>
      <input class="input" type="text" name="email" required>
    </td>
    <td>
      <label for="password">Password:</label></br>
      <input class="input" type="text" name="password" required>
    </td>
  </tr>
  <tr>
    <td>
      <label for="bikeSize">Bike Size:</label></br>
      <select class="input" name="bike">
      <option value="1">450</option>
      <option value="2">350</option>
      <option value="3">300</option>
      <option value="4">250</option>
      <option value="5">125</option>
      </select>
    </td>
    <td>
      <label for="terrainType">Select a Terrain:</label></br>
      <select class="input" name="terrain">
      <option value="1">Mountain</option>
      <option value="2">Desert</option>
      <option value="3">Rocks n' Logs</option>
      </select>
    </td>
  </tr>
  <tr>
    <td>
      <button type="submit" id="submit">Submit</button>
    </td>
    <td>  
      <button type="reset" id="clear">Clear Form</button>
    </td>
  </tr>
  </table>
</form></br>
  <div id='test'><div>
  <p class="location"> All races will be held on June 22nd Participants will be notified of the location on the 10th of June.</p>
  <table id="display">
  <tr class="easyRead">
  <th>First Name</th>
  <th>Last Name</th>
  <th>Terrain Chosen</th>
  <th>Bike Size</th>
  </tr>
<?php
try
{
  foreach ($db->query('SELECT t1.id, t1.firstname, t1.lastname, t1.terrain_id, t1.bikes_id, t2.id, t2.terrain_type, t3.id, t3.bike_type
   FROM racers t1 INNER JOIN terrain t2 ON t1.terrain_id = t2.id
   INNER JOIN bikes t3 ON t1.bikes_id = t3.id ORDER BY t1.id ASC')as $row)
  {
    echo '<tr class="easyRead"><form action=\'login.php\' method=\'POST\'><td>' . $row['firstname'] . '</td><td>' . $row['lastname'] . 
         '</td><td>' . $row['terrain_type']. '</td><td>' . $row['bike_type']. 
         '</td><td><button type=\'submit\' name=\'edit\'>Edit</button></form></tr>';            
  }
}
catch (PDOExecption $ex)
{
  echo "Error with DB. Details: $ex";
  die(); 
}

?>
  </table>
</body>
</html>

