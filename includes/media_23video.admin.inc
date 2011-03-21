<?php

/**
 * @file media_23video/includes/media_23video.admin.inc
 * Administrative functions for Media: 23 Video.
 */

/**
 * The administrative settings form for Media: 23 Video.
 */
function media_23video_settings() {
  $form = media_23video_admin_form();
  $form['settings_info'] = array(
    '#type' => 'item',
    '#value' => 'These settings specifically affect videos displayed from 23 Video.',
    '#weight' => -10,
  );
  return system_settings_form($form);
}

/**
 * This form will be displayed both at /admin/settings/media_23video and
 * admin/content/emfield.
 */
function media_23video_admin_form() {
  $form[media_23video_variable_name('domain')] = array(
    '#type' => 'textfield',
    '#title' => t('Domain for your 23 Video site'),
    '#default_value' => media_23video_variable_get('domain'),
  );
  return $form;
}
