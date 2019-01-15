<?php 
/**
 * Copyright (C) 2019 Paladin Business Solutions Inc.
 *
 */

error_reporting(E_ALL);
ini_set('display_errors', 0);

require( '../../../../wp-load.php' );
$email_confirmation_page = site_url() . "/email-confirmation" ;

// locate the email address to be removed.
$contact_id = $_GET['contact_id'] ;

global $wpdb;

$sql  = "UPDATE `nomad_contacts` SET `email_confirmed` = 1 "   ;
$sql .= "WHERE `nomad_contacts`.`nomad_contacts_id` = $contact_id ";

$wpdb->query($sql);

// then re-direct to public page confirming the email removal.
header("Location: $email_confirmation_page");
?>