<?php
	session_start();
	require "dbConnect.php";
	$db = get_db();

	$firstname = $_POST['firstName'];
	$lastname  = $_POST['lastName'];
	$password = $_POST['password'];
	$email = $_POST['email'];
	$terrain = $_POST['terrain'];
	$bike = $_POST['bike'];


	echo $firstname . "<br/>";
	echo $lastname . "<br/>";
	echo $password. "<br/>";
	echo $email. "<br/>";
	echo $bike. "<br/>";
	echo $terrain. "<br/>";
	echo $_SESSION['rider'];

	try
	{
		$query = "UPDATE racers SET firstname = :firstname, lastname = :lastname, password = :password, email = :email, terrain_id = :terrain_id, bikes_id = :bikes_id WHERE id = :id";

		$statement = $db->prepare($query);

		$statement->bindValue(":firstname", $firstname);
		$statement->bindValue(":lastname", $lastname);

		// Hash the password
		$hashedPassword = password_hash($password, PASSWORD_DEFAULT);
		$statement->bindValue(":password", $hashedPassword);
		$statement->bindValue(":email", $email);
		$statement->bindValue(":terrain_id", $terrain);
		$statement->bindValue(":bikes_id", $bike);
		$statement->bindValue(":id", $_SESSION['rider']);

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