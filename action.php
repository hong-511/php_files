<?php	
    echo "Hi! This is action.php file.<br/> ";
    
    if(!isset($_GET["username"]))
            echo "Could you tell me your name?<br/>";
    else
        echo "Hi, Your name is ". $_GET["username"].".<br/>";
    
    if(!isset($_GET["password"]))
        echo "Please enter your password.<br/>";
    else
        echo "Your password is". $_GET["password"].".<br/>";

    if(!isset($_GET["clothessize"]))
        echo "Please select your clothes size.<br/>";
    else
        echo "Your CLothes Size is ". $_GET["clothessize"].".<br/>";
        
    if(!isset($_GET["eatingtime"]))
        echo "Do you eat Breakfast/ Lunch/ Dinner ?<br/>";
    else{
        $eatTime = $_GET["eatingtime"];
        foreach($eatTime as $times){
            echo "You eat at ". $times. ".<br/>";
        }
    }						
    if(!isset($_GET["gender"]))
		echo "Please select your gender.<br/>";
	else
        echo "Your Gender is ".$_GET["gender"].".<br/>";
        
    echo "Bye!";
?>
