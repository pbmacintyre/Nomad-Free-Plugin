<?php
/**
 * Copyright (C) 2019 Paladin Business Solutions Inc.
 *
 */
/* ============================================= */
/* if the constant is not defined then get out ! */
/* ============================================= */
if (!defined('WP_UNINSTALL_PLUGIN')) exit() ;

/* ======================================== */
// Drop the DB tables related to the plugin */
/* ======================================== */
global $wpdb;
// $wpdb->query('DROP TABLE nomad_contacts');
// $wpdb->query('DROP TABLE nomad_control');
// $wpdb->query('DROP TABLE nomad_help');
?>