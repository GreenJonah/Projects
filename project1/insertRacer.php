<?php

$firstname = $_POST['firstName'];
$lastname  = $_POST['lastName'];
$password = $_POST['password'];
$email = $_POST['email'];
$terrain = $_POST['terrain'];
$bike = $_POST['bike'];

if (!isset($firstname)   || $firstname == ""
	|| !isset($lastname) || $lastname  == ""
	|| !isset($password) || $password  == ""
	|| !isset($email)    || $email     == ""
    || !isset($terrain)  || $terrain   == ""
    || !isset($bike)     || $bike      == "")
{
	header("Location: project1.php");
	die(); 
}
/*
echo $firstname . "<br/>";
echo $lastname . "<br/>";
echo $password. "<br/>";
echo $email. "<br/>";
echo $bike. "<br/>";
echo $terrain. "<br/>";
*/

// Hash the password
$hashedPassword = password_hash($password, PASSWORD_DEFAULT);

require("dbConnect.php");
$db = get_db();

try
{
	$query = "INSERT INTO racers(firstname, lastname, password, email, terrain_id, bikes_id) VALUES (:firstname, :lastname, :password, :email, :terrain_id, :bikes_id)";

	$statement = $db->prepare($query);

	$statement->bindValue(":firstname", $firstname);
	$statement->bindValue(":lastname", $lastname);
	$statement->bindValue(":password", $hashedPassword);
	$statement->bindValue(":email", $email);
	$statement->bindValue(":terrain_id", $terrain);
	$statement->bindValue(":bikes_id", $bike);

	$statement->execute();
}
catch(Exeption $ex)
{
	// Please be aware that you don't want to output the Exception message in
	// a production environment
	echo "Error with DB. Details: $ex";
	die();
}
header("Location: project1.php");
die();

?>
