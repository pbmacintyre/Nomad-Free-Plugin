<?php
/**
 * Copyright (C) 2019 Paladin Business Solutions Inc.
 *
 */

/* =============================== */
/* send out welcome email function */
/* =============================== */
function send_welcome_email($email, $contact_id, $full_name) {
    $confirm_url = plugins_url('/', __FILE__) . "nomad-confirm-optin.php?contact_id=" . $contact_id;
    $confirm_url .= "&method=1" ;
    $subject = 'Nomad PHP - Please confirm your signup';
    
    $message = "Hi $full_name: <br/><br/>Thanks for joining our newsletter sign up process. ";
    $message .= "<br/><strong>[If this was not you please ignore this email]</strong><br/>";    
    $message .= "<br/>Please follow this link to confirm your subscription to our email notification list: <br/> ";
    $message .= "<a href='$confirm_url'> Confirm sign up </a>";
    
    // Send email to new sign up email.
    $headers = array('Content-Type: text/html; charset=UTF-8');
    wp_mail( $email, $subject, $message, $headers );
} // end send_welcome_email function

/* ============================================== */
/* generate unique ID for new subscriber function */
/* ============================================== */
function unique_token() {
    global $wpdb;
    $result = $wpdb->get_row( $wpdb->prepare("SELECT `token_prefix`
            FROM `nomad_control` WHERE `nomad_control_id` = %d", 1 )
        );
    $prefix = $result->token_prefix ;
    return uniqid($prefix, true) ;
}

/* ============================== */
/* Build help icon and title text */
/* ============================== */
function build_help($field) {
    global $wpdb;
    $image_source = NOMAD_PLUGINDIR . 'images/question_mark.png' ;
    
    $result_help = $wpdb->get_row( $wpdb->prepare("SELECT nomad_help_help AS help_text
            FROM `nomad_help` WHERE `nomad_help_field` = %s", $field) );

    $out_string = "<img src='$image_source' title='$result_help->help_text' />" ;
    return $out_string ;
}
?>