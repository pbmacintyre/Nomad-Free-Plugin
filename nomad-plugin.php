<?php 
error_reporting(E_ALL);
ini_set('display_errors', 0);
/*
 Plugin Name: Nomad Sample
 Plugin URI:  https://paladin-bs.com/plugins/
 Description: Plugin sample for teaching plugin Development.
 Author:      Peter MacIntyre
 Version:     1.2
 Author URI:  https://paladin-bs.com/peter-macintyre/
 Details URI: https://paladin-bs.com
 License:     GPL2
 License URI: https://www.gnu.org/licenses/gpl-2.0.html

Nomad Sample is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
any later version.
 
Nomad Sample is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
 
See License URI for full details.
*/

/* ============================== */
/* Set Nomad Constant values */
/* ============================== */

if(!defined('NOMAD_PLUGINDIR')){
    define('NOMAD_PLUGINDIR', plugin_dir_url(__FILE__) ) ;
}
if(!defined('NOMAD_PLUGIN_INCLUDES')){
    define('NOMAD_PLUGIN_INCLUDES', plugin_dir_url(__FILE__) . "includes/" ) ;
}
if(!defined('NOMAD_PLUGIN_FILENAME')){
    define ('NOMAD_PLUGIN_FILENAME', plugin_basename(dirname(__FILE__) . '/nomad.php') ) ;
}
if(!defined('NOMAD_PRO_URL')){
    define ('NOMAD_PRO_URL', 'https://paladin-bs.com/product/nomad-pro/') ;
}
if(!defined('NOMAD_LOGO')){
    define ('NOMAD_LOGO', NOMAD_PLUGINDIR . 'images/nomad-logo.jpg' ) ;
}
/* ============================================ */
if(!defined('NOMAD_SPACER')){
    $spacer = "<br/>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; " ;
    define ('NOMAD_SPACER', $spacer) ;
}
/* ========================== */
/* set nomad supporting cast  */
/* ========================== */
function nomad_js_add_script() {
    $js_path = NOMAD_PLUGINDIR . 'js/nomad-scripts.js' ;
    wp_enqueue_script('nomad-js', $js_path) ;
}
add_action('init', 'nomad_js_add_script');

function nomad_css_add_script() {
    $styles_path = NOMAD_PLUGINDIR . 'css/nomad-custom.css' ;
    wp_enqueue_style('nomad-css', $styles_path) ;
}

add_action('init', 'nomad_css_add_script');

// call add action func on menu building function below.
add_action('admin_menu', 'nomad_menu');

/* ========================================= */
/* Make top level menu                       */
/* ========================================= */
function nomad_menu(){
    add_menu_page(
        'Nomad Free: Nomad Settings',    // Page & tab title
        'Nomad Free',                          // Menu title
        'manage_options',                     // Capability option
        'nomad_Admin',                        // Menu slug
        'nomad_config_page',                  // menu destination function call
        NOMAD_PLUGINDIR . 'images/nomad-icon.jpg', // menu icon path
        //         'dashicons-phone', // menu icon path from dashicons library
        25 );                                       // menu position level
        
        add_submenu_page(
            'nomad_Admin',                // parent slug
            'Nomad Free: Nomad Configurations', // page title
            'Settings',                            // menu title - can be different than parent
            'manage_options',                      // options
            'nomad_Admin' );                 // menu slug to match top level (go to the same link)
        
        add_submenu_page(
            'nomad_Admin',                   // parent menu slug
            'Nomad Free: Manage Subscribers', // page title
            'List Subscribers',                    // menu title
            'manage_options',                      // capability
            'nomad_list_subs',               // menu slug
            'nomad_list_subscribers'         // callable function
            );
        
        add_submenu_page(
            'nomad_Admin',                // parent menu slug
            'Nomad Free: Add a New Subscriber', // page title
            'Add Subscribers',                  // menu title
            'manage_options',                   // capability
            'nomad_add_subs',             // menu slug
            'nomad_add_subscribers'       // callable function
            );
}

/* ========================================= */
/* page / menu calling functions             */
/* ========================================= */
// function for default Admin page
function nomad_config_page() {
    // check user capabilities
    if (!current_user_can('manage_options')) { return; }
    require_once(NOMAD_PLUGIN_INCLUDES . "nomad-config-page.inc"); 
}

// function for editing existing subscribers page
function nomad_list_subscribers() {
    // check user capabilities
    if (!current_user_can('manage_options')) { return; }
    require_once(NOMAD_PLUGIN_INCLUDES . "nomad-list-subscribers.inc"); 
}

// function for adding new subscribers page
function nomad_add_subscribers() {
    // check user capabilities
    if (!current_user_can('manage_options')) { return; }
    require_once(NOMAD_PLUGIN_INCLUDES . "nomad-add-subscribers.inc"); 
}

/* ================================== */
/* Add action for the contacts widget */
/* ================================== */
add_action('widgets_init', 'nomad_register_contacts_widget');

/* ============================================== */
/* Add contacts widget function                   */
/* This registers the nomad_contacts_widget       */
/* ============================================== */
function nomad_register_contacts_widget() {
  register_widget('nomad_contacts_widget') ;  // class name in following inc file 
}

require_once(NOMAD_PLUGIN_INCLUDES . "nomad-contacts-widget.inc");

/* ================================================== */
/* Add action & function calls for a dashboard widget */
/* ================================================== */
add_action('wp_dashboard_setup', 'nomad_dashbaord_sample');

function nomad_dashbaord_sample() {
    wp_add_dashboard_widget('dashboard_custom_feed', 'Nomad Free Plugin Info','dashboard_example_display') ;
}

function dashboard_example_display() {
    echo "<font color=red>Nomad Plugin Demo - help is on the way! </font>" ;
}

/* ========================== */
/* Add shortcode for contacts */
/* ========================== */
add_shortcode( 'nomad_contacts', 'nomad_contacts_scode' );

/* ======================================= */
/* Add contacts short code function        */
/* This registers the nomad_contacts_short */
/* ======================================= */
function nomad_contacts_scode() {
    require_once(NOMAD_PLUGIN_INCLUDES . "nomad-subscribers-shortcode.inc");    
}
 
/* ============================================== */
/* Add action hook for correspondence on new post */
/* ============================================== */

add_action( 'pending_to_publish', 'nomad_new_post_send_notifications');
add_action( 'draft_to_publish', 'nomad_new_post_send_notifications');

function nomad_new_post_send_notifications( $post ) {
    global $wpdb ;    
    $result = $wpdb->get_row( $wpdb->prepare("SELECT `email_updates` FROM `nomad_control`
        WHERE `nomad_control_id` = %d", 1)  );    
    // If this is a revision, don't send the correspondence.
    if (wp_is_post_revision( $post->ID )) return;
    
    // this is also triggered on a page publishing, so ensure that the type is a Post and then carry on    
    if (get_post_type($post->ID) === 'post') {    
        // only send out correspondence if set in control / admin
        if ($result->email_updates) { require_once(NOMAD_PLUGIN_INCLUDES . "nomad-send-mass-email.inc"); }        
    }
}
/* ============================================= */
/* Add registration hook for plugin installation */
/* ============================================= */
register_activation_hook(__FILE__, 'nomad_install');
register_activation_hook(__FILE__, 'activation_code');

function nomad_install() {
    require_once(NOMAD_PLUGIN_INCLUDES . "nomad-install.inc");
}
/* ========================================= */
/* Create default pages on plugin activation */
/* ========================================= */
function activation_code(){
    require_once(NOMAD_PLUGIN_INCLUDES . "nomad-activation.inc");
}

/* ================================ */
/* bring in generic nomad functions */
// /* ================================ */
require_once("includes/nomad-functions.inc");

/* ====================================================== */
/* add link on plugin details line for buying Pro Version */
/* ====================================================== */
// add_filter('plugin_row_meta', 'nomad_get_pro', 10, 2);

//Add a link on the plugin control line after 'visit plugin site'
/*
function rc_get_pro($links, $file) {
    if ( $file == NOMAD_PLUGIN_FILENAME ) {
        $link_string = NOMAD_PRO_URL ;
        $links[] = "<a href='$link_string' style='color: red' target='_blank'>" . esc_html__('Get Pro Version', 'RCCP_free') . '</a>';
    }
    return $links;
}
?>