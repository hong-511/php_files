<html>
	<head>
		<title> 00957043 </title>
	</head>
	
	<body>		
			<h1> My PHP Homework </h1>
			<p> By <font size="5"> <strong>00957043</strong> </font></p>
			<hr>
	<!-- form  -->
		<?php 
			echo "Hi! This is php_pratice.php file.<br/> ";
			echo "I can print something on this by echo function.<br/>";
        ?>
		<form  action=action.php method="get">
			<!-- text -->
			<?php
				if(!isset($_GET["username"]))
					echo "Could you tell me your name?<br/>";
			?>
			<div>
				<label><font size="3"> <strong>User name :</strong> </font></label>
				<input type="text" name="username" />
			</div><br/>
			<?php
				if(!isset($_GET["password"]))
					echo "Please enter your password.<br/>";
			?>
			<div>
				<label><font size="3"> <strong>Password :</strong> </font></label>
				<input type="password" name="password"><br/>
			</div><br/>
			
			<hr>
			<!-- select -->
			<?php
				if(!isset($_GET["clothessize"]))
					echo "Please select your clothes size.<br/>";
			?>
			<div>
				<label><font size="3"> <strong>Clothes Size :</strong> </font></label>
				<select name="clothessize">
					<option value = "S">S</option>
					<option value = "M">M</option>
					<option value = "L">L</option>
				</select>
			</div>
			<hr>
			<!-- checkbox -->
			<?php
				if(!isset($_GET["eatingtime"]))
					echo "Do you eat Breakfast/ Lunch/ Dinner ?<br/>";					
			?>
			<div>
				<label><font size="3"> <strong>Eating Time :</strong> </font></label><br/>
				<input type="checkbox" name="eatingtime[]" value="moring">Breakfast<br/>
				<input type="checkbox" name="eatingtime[]" value="noon">Lunch<br/>
				<input type="checkbox" name="eatingtime[]" value="night">Dinner<br/>
			</div><br/>
			
			<hr>
			<!-- radio -->
			<?php
				if(!isset($_GET["gender"]))
					echo "Please select your gender.<br/>";
			?>
			<div>
				<label><font size="3"> <strong>Gender :</strong> </font></label><br/>
				<input type="radio" name="gender" value="male">Male<br/>
				<input type="radio" name="gender" value="female">Female<br/>
			</div><br/>
			
			<hr>
			<!-- submit -->
			<div>
				<input type="submit" value="Submit">
			</div>
		</form>
	</body>	
</html>