<?php
	session_start();
	$badLogin = false;

	if (isset($_POST['emailCheck']) && isset($_POST['passwordCheck']))
	{
		$email = $_POST['emailCheck'];
		$password = $_POST['passwordCheck'];

		// Connect to DB
		require "dbConnect.php";
	  	$db = get_db();

		$query = 'SELECT id, password FROM racers WHERE email = :email';
		$statement = $db->prepare($query);
		$statement->bindValue(':email', $email);
		$result = $statement->execute();
		if ($result)
		{	
			$row = $statement->fetch();
			$hashedPasswordFromDB = $row['password'];
	
			// Check to see if the hashes match
			if (password_verify($password, $hashedPasswordFromDB))
			{	
				// Password was correct
				$_SESSION['rider'] = $row['id'];
				header("Location: edit.php");
				die(); 
			}
			else
			{
			
				$badLogin = true;
			}
		}
		else
		{
			$badLogin = true;
		}
	}	
?>
<!DOCTYPE html>
<html>
<head>
	<title>login</title>
	<link rel="stylesheet" type="text/css" href="project1.css">
</head>
<body>
	<p id="title">Please Login</p>
	<?php
  	if ($badLogin)
  	{
    	 echo "<p class=\"notCorrect\">Incorrect email address or password!</p><br/><br/>\n";
  	}
  	?>
	<form action="login.php" method="POST">
	<table class="enter">
		<tr>
		<td>
			<label for="email">Email Address:</label></br>
      		<input class="input" type="text" id="emailCheck" name="emailCheck" value=''>	
		</td>
		</tr>
		<tr>
			<td>
				<label for="password">Password:</label></br>
      			<input class="input" type="password" id="passwordCheck" name="passwordCheck" value=''>
			</td>
		</tr>
		<tr>
	    <td>
	      <input type="submit" id="login" value='login'>
	    </td>
	    </form>
	    <td>  
	      	<form action="project1.php">
    			<input type="submit" value="Go Back" />
			</form>
	    </td>
		</tr>
	</table>
</body>
</html>