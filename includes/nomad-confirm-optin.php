<?php 
/**
 * Copyright (C) 2019 Paladin Business Solutions Inc.
 *
 */

error_reporting(E_ALL);
ini_set('display_errors', 0);

require( '../../../../wp-load.php' );
global $wpdb;

// locate the email address to be removed.
$contact_id = $_GET['contact_id'] ;
$method     = $_GET['method'] ;
$opt_in_date = date('Y-m-d'); // YYYY-MM-DD
$opt_in_ip = $_SERVER['REMOTE_ADDR']?:($_SERVER['HTTP_X_FORWARDED_FOR']?:$_SERVER['HTTP_CLIENT_IP']);  ;

if ($method == 1) { // email confirmation coming in
    $confirmation_page = site_url() . "/email-confirmation" ;    
    $sql = $wpdb->prepare("UPDATE `nomad_contacts` 
        SET `email_confirmed` = %d, `email_optin_ip` = %s, `email_optin_date` = %s 
        WHERE `nomad_contacts_id` = %s",
        1, $opt_in_ip, $opt_in_date, $contact_id ) ;    
} 

$wpdb->query($sql);

// then re-direct to public page confirming the appropriate opt-in method.
header("Location: $confirmation_page");
?>