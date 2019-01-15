<?php
/**
 * Copyright (C) 2019 Paladin Business Solutions Inc.
 *
 */
error_reporting(E_ALL & ~E_NOTICE);
ini_set('display_errors', 0);

/* ========= */
/* show_form */
/* ========= */
Function show_form($message, $label = "", $color = "#008EC2") {	
	global $print_again, $wpdb;    ?>    
     <div class="wrap"> 
    <img id='page_title_img' title="Nomad Sample Plugin" src="<?= NOMAD_LOGO ;?>">
    <h1 id='page_title'><?= esc_html(get_admin_page_title()); ?></h1>
    
    <form action="<?php echo NOMAD_PRO_URL ?>" target="_blank" style="padding-left: 15%;">
        <?php 
        $btn_attributes = array( "style" => "background: red; border-color: #006799; color: #fff;" ); 
        submit_button("Get Pro Version","","submit","",$btn_attributes);
        ?>        
    </form>
    	
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
	
	$nomad_result = $wpdb->get_row( $wpdb->prepare("SELECT * FROM `nomad_control`
        WHERE `nomad_control_id` = %d", 1)
	    );
	?></td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "email_updates") echo "color:red"; ?>' >Send Post Updates by eMail?</p>			
		</td>
		<td class="right_col"><input type="checkbox" name="email_updates" <?php 
		if ($print_again) { 
		    if ($_POST['email_updates'] == "on") {
		      echo 'CHECKED';
		    } 
          } else {             
              if ($nomad_result->email_updates == 1) {
                  echo 'CHECKED' ;
                }
          }
            ?>></td>
	</tr> 	
	<tr class="TableOverride">
		<td class="left_col">
		<p style='display: inline; <?php if ($label == "nomad_user_name") echo "color:red"; ?>' >Username:</p>
		<p style='color: red; display: inline'>*</p>
        
        <?php echo build_help("username") ; ?>
              
		</td>
		<td class="right_col"><input type="text" name="nomad_user_name" value="<?php 
		  if ($print_again) {
		      echo $_POST['nomad_user_name'];
          } else {             
              if ($nomad_result->nomad_user_name) {
                  echo $nomad_result->nomad_user_name ;
              } else {
                echo "&nbsp;" ;  
              }
          }
            ?>"></td>
	</tr>	
	<tr class="TableOverride">
		<td class="left_col">
			<p style='display: inline; <?php if ($label == "token_prefix") echo "color:red"; ?>' >Token Prefix:</p>
            <!--  <p style='color: red; display: inline'>*</p>   -->
             
            <?php echo build_help("token_prefix") ; ?>
                         
		</td>
		<td class="right_col"><input type="text" name="token_prefix" style="width: 25%;" value="<?php 
		  if ($print_again) {
		      echo $_POST['token_prefix'];
          } else {             
              if ($nomad_result->token_prefix) {
                  echo $nomad_result->token_prefix ;
              } 
          }
            ?>"></td>
	</tr>	
	<tr class="TableOverride">
		<td colspan="2" align="center">			
			<br/>
			<?php 
			$btn_attributes = array( "style" => "background: #008ec2; border-color: #006799; color: #fff;" );
			submit_button("Save Settings","","submit","",$btn_attributes); ?>
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
	
	$label = "" ;
	$message = "" ;	
	
	/* data integrity checks */	
		
	if ($_POST['nomad_user_name'] == "") {
	    $print_again = true;
	    $label = "nomad_user_name";
	    $message = "<b>Username field cannot be blank.</b>";
	}	

	// end data integrity checking
	
	if ($print_again == true) {
		$color = "red" ;
	    show_form($message, $label, $color);
	} else {	    
	    /* convert and / or sanitize any needed form POST values */
	   
        if ($_POST['email_updates'] == "on") {
            $email_updates = 1;
        } else {
            $email_updates = 0;
        }
        
        $token_prefix          = $_POST['token_prefix'] ;
        
        $config_sql = $wpdb->prepare("UPDATE `nomad_control` SET
            `email_updates` = %d, `nomad_user_name` = %s, `token_prefix` = %s
            WHERE `nomad_control_id` = %d",
            $email_updates,  $_POST['nomad_user_name'], $token_prefix, 1) ;
        
        $wpdb->query( $config_sql ); 
        
	    $color = "#53DF00";
	    $message = "Configuration Changes have been saved";	   
	    show_form($message, $label, $color) ;
	}
}

/* ============= */
/*  --- MAIN --- */
/* ============= */
if(isset($_POST['submit'])) {
	check_form();
} else {
	$message = "Adjust settings to your preferences";
	show_form($message);
} 
?>