<?php
/**
 * Copyright (C) 2019 Paladin Business Solutions Inc.
 *
 */

error_reporting(E_ALL);
ini_set('display_errors', 0);

/* ========= */
/* show_form */
/* ========= */
Function show_form($message, $label = "", $color = "green") {	
	global $print_again, $wpdb;  ?>		
	<div class="wrap">
    <img id='page_title_img' title="Nomad Sample Plugin" src="<?= NOMAD_LOGO ;?>">
    <h1 id='page_title'><?= esc_html(get_admin_page_title()); ?></h1>    
    
    <form action="" method="post" >
	<table class="TableOverride" >
		<tr class="TableOverride">
			<td colspan="2" align="center">
<?php	
	if ($print_again == true) {
		echo "<font color='$color'><strong>" . $message . "</strong></font>";
	} else {
	    echo "<font color='$color'><strong>" . $message . "</strong></font>";
	}	
	?></td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "full_name") echo "color:red"; ?>' >Full Name:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col">
			<input type="text" name="full_name" value="<?php if ($print_again) { echo $_POST['full_name']; } ?>">
		</td>
	</tr>
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "email") echo "color:red"; ?>' >email:</p>
			<p style='color: red; display: inline'>*</p>
		</td>
		<td class="right_col">
			<input type="text" name="email" value="<?php if ($print_again) { echo $_POST['email']; } ?>">
		</td>
	</tr>	
	<tr class="TableOverride">
		<td colspan="2" align="center">			
			<br/>
			<?php 
			$other_attributes = array( "style" => "background: #008ec2; border-color: #006799; color: #fff;" );
			submit_button("Save Settings","","submit","",$other_attributes); ?>
			<br/><br/>
		</td>
	</tr>
	</table>
	</form>
</div>
<?php
}

/* ========== */
/* check_form */
/* ========== */
Function check_form() {
	
	global $print_again, $wpdb;
	
	$full_name  = $_POST['full_name'] ;
	$email      = $_POST['email'] ;	
	
	/* =================================== */
    /* data integrity checks, data massage */
    /* =================================== */        
	
    if ($email == "" && $mobile == "") {        
        $print_again = true;
        $label = "email";
        $return_message = "eMail and Mobile cannot both be blank.";
    }
    if ($email !== "" && filter_var($email, FILTER_VALIDATE_EMAIL) == FALSE){
        $print_again = true;
        $label = "email";
        $return_message = "eMail is malformed";
    }
    if ($full_name == "") { 
        $print_again = true;
        $label = "full_name";
        $return_message = "Full Name cannot be blank."; 
    }    
    /* ========================== */
    /* end data integrity checks  */
    /* ========================== */	
    
    //   echo "</br> Trimmed mobile: [" . $mobile ."]";
    
	if ($print_again == true) {
	    show_form($return_message, $label, 'red');
	} else {	    
	    /* ========================== */
	    /* prep for saving the data   */
	    /* ========================== */
	    
	    // if only given an email, check to see if we already have it
	    if ($email != "" ) {
	        $result = $wpdb->get_row( $wpdb->prepare("SELECT `nomad_contacts_id`
                    FROM `nomad_contacts` WHERE `email` = %s",
	            $email )
	            );
	        if ($result->nomad_contacts_id) {
	            $return_message = "<br/><center>That email is already on file.</center>" ;
	        } else {
	           	            
	            // save with name	            
	            $wpdb->query( $wpdb->prepare("INSERT INTO
                        `nomad_contacts` (`full_name`, `email`)
                        VALUES (%s, %s )",
                        $full_name, $email )
	            );	            
	            send_welcome_email($email, $wpdb->insert_id, $full_name );
	            $return_message = "<br/><center>Contact Information saved...the new member will still have to opt-in</center>" ;
	        }
	    }
        $color = "red";	    
	    show_form($return_message,'',$color) ;	
	}	    
}

/* ============= */
/*  --- MAIN --- */
/* ============= */
if(isset($_POST['submit'])) {
	check_form();
} else {
	$message = "Provide the data for the new subscriber";
	show_form($message);
} 
?>