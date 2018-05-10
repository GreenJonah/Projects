<?php
	session_start();
	require "dbConnect.php";
  	$db = get_db();	
?>
<!DOCTYPE html>
<html>
<head>
	<title>Edit Profile</title>
	<link rel="stylesheet" type="text/css" href="project1.css">
</head>
<body>
	<p id="title">Edit Profile</p>
<form action="update.php" method="POST">
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
    </form>
      <form action="project1.php">
    	<input type="submit" value="Back to Main page" />
	  </form>
    </td>
  </tr>
  </table>
</body>
</html>