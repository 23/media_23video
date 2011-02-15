<?php
// $Id: 23video.inc,v 1.1.2.3 2010/09/23 21:09:42 aaron Exp $

/**
 * @file media_23video/includes/providers/23video.inc
 *   Provide support for the 23video provider to the emfield.module.
 */

/**
 * hook emvideo_PROVIDER_info
 * this returns information relevant to a specific 3rd party video provider
 * @return
 *   an array of strings requested by various admin and other forms
 *   'name' => the translated name of the provider
 *   'url' => the url to the main page for the provider
 *   'settings_description' => a description of the provider that will be posted in the admin settings form
 *   'supported_features' => an array of rows describing the state of certain supported features by the provider.
 *      These will be rendered in a table, with the columns being 'Feature', 'Supported', 'Notes'.
 */
function emvideo_23video_info() {
  $features = array(
    array(t('Autoplay'), t('Yes'), ''),
    array(t('Thumbnails'), t('Yes'), t('')),
    array(t('Full screen mode'), t('Yes'), t('You may customize the player to enable or disable full screen playback. Full screen mode is enabled by default.')),
  );
  return array(
    'provider' => '23video',
    'name' => t('23 Video'),
    'url' => MEDIA_23VIDEO_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from 23 Video'),
    'supported_features' => $features,
  );
}

/**
 * hook emvideo_PROVIDER_settings
 * this should return a subform to be added to the emvideo_settings() admin settings page.
 * note that a form field will already be provided, at $form['PROVIDER'] (such as $form['23video'])
 * so if you want specific provider settings within that field, you can add the elements to that form field.
 */
function emvideo_23video_settings() {
  module_load_include('inc', 'media_23video', 'includes/media_23video.admin');
  return media_23video_admin_form();
}




/**
 * hook emfield_PROVIDER_data
 *
 * provides an array to be serialised and made available with $item elsewhere
 */
function emvideo_23video_data($field, $item) {
  $xml = emfield_request_xml('23video', 'http://reinvent.23video.com/oembed', array('url'=>'http://reinvent.23video.com' . $item['value']), TRUE, FALSE, $item['value']);
  $html = $xml['OEMBED']['HTML'][0];
  $data = array();
  $data['emvideo_23video_version'] = EMVIDEO_23VIDEO_DATA_VERSION;
  if (isset($xml['OEMBED']['THUMBNAIL_URL'])) {
    $data['thumbnail'] = $xml['OEMBED']['THUMBNAIL_URL'][0];
  } else {
    $data['thumbnail'] = 'http://www.23video.com/resources/23-style/graphics/void.gif';
  }
  $data['embed'] = $html;
  return $data;
}


/**
 * hook emvideo_PROVIDER_extract
 * this is called to extract the video code from a pasted URL or embed code.
 * @param $embed
 *   an optional string with the pasted URL or embed code
 * @return
 *   either an array of regex expressions to be tested, or a string with the video code to be used
 *   if the hook tests the code itself, it should return either the string of the video code (if matched), or an empty array.
 *   otherwise, the calling function will handle testing the embed code against each regex string in the returned array.
 */
function emvideo_23video_extract($embed = '') {
  return array(
    '@reinvent.23video\.com([^\?]+)@i',
  );
}

/**
 * hook emvideo_PROVIDER_embedded_link($video_code)
 * returns a link to view the video at the provider's site
 *  @param $video_code
 *    the string containing the video to watch
 *  @return
 *    a string containing the URL to view the video at the original provider's site
 */
function emvideo_23video_embedded_link($video_code) {
  return 'http://reinvent.23video.com' . $video_code;
}

/**
 * The embedded flash displaying the 23video video.
 */
function theme_emvideo_23video_flash($item, $width, $height, $autoplay) {
  $req = array('url'      => 'http://reinvent.23video.com' . $item['value'],
               'width'    => $width,
               'height'   => $height,
               'autoplay' => $autoplay
               );
  $xml = emfield_request_xml('23video', 'http://reinvent.23video.com/oembed', $req, TRUE, FALSE, $item['value']);
  return($xml['OEMBED']['HTML'][0]);
}

/**
 * hook emvideo_PROVIDER_thumbnail
 * returns the external url for a thumbnail of a specific video
 * TODO: make the args: ($embed, $field, $item), with $field/$item provided if we need it, but otherwise simplifying things
 *  @param $field
 *    the field of the requesting node
 *  @param $item
 *    the actual content of the field from the requesting node
 *  @return
 *    a URL pointing to the thumbnail
 */
function emvideo_23video_thumbnail($field, $item, $formatter, $node, $width, $height) {
  return $item['data']['thumbnail'];
}

/**
 * hook emvideo_PROVIDER_video
 * this actually displays the full/normal-sized video we want, usually on the default page view
 *  @param $embed
 *    the video code for the video to embed
 *  @param $width
 *    the width to display the video
 *  @param $height
 *    the height to display the video
 *  @param $field
 *    the field info from the requesting node
 *  @param $item
 *    the actual content from the field
 *  @return
 *    the html of the embedded video
 */
function emvideo_23video_video($embed, $width, $height, $field, $item, &$node, $autoplay) {
  $output = theme('emvideo_23video_flash', $item, $width, $height, $autoplay);
  return $output;
}

/**
 * hook emvideo_PROVIDER_video
 * this actually displays the preview-sized video we want, commonly for the teaser
 *  @param $embed
 *    the video code for the video to embed
 *  @param $width
 *    the width to display the video
 *  @param $height
 *    the height to display the video
 *  @param $field
 *    the field info from the requesting node
 *  @param $item
 *    the actual content from the field
 *  @return
 *    the html of the embedded video
 */
function emvideo_23video_preview($embed, $width, $height, $field, $item, &$node, $autoplay) {
  error_log('emvideo_23video_preview');
  $output = theme('emvideo_23video_flash', $item, $width, $height, $autoplay);
  return $output;
}

/**
 * Implementation of hook_emfield_subtheme.
 */
function emvideo_23video_emfield_subtheme() {
  error_log('emvideo_23video_emfield_subtheme');
    $themes = array(
        'emvideo_23video_flash'  => array(
            'arguments' => array('item' => NULL, 'width' => NULL, 'height' => NULL, 'autoplay' => NULL),
            'file' => 'providers/23video.inc',
            'path' => drupal_get_path('module', 'media_23video'),
        )
    );
    return $themes;
}


