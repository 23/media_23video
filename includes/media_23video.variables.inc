<?php
// $Id: media_23video.variables.inc,v 1.1.2.1 2010/09/23 21:04:55 aaron Exp $

/**
 * @file media_23video/includes/media_23video.variables.inc
 * Contains the variables and defaults used by Media: 23 Video.
 */

/**
 * The variable namespace for Media: 23 Video.
 */
define('MEDIA_23VIDEO_NAMESPACE', 'media_23video__');

/**
 * This is the main URL for 23 Video.
 */
define('MEDIA_23VIDEO_MAIN_URL', 'http://www.23video.com/');

/**
 * This is the URL to the API of 23 Video.
 */
define('MEDIA_23VIDEO_API_INFO', 'http://www.23developer.com/api/');

/**
 * This defines the version of the content data array that we serialize
 * in data(). If we change the expected keys of that array,
 * we must increment this value, which will allow older content to be updated
 * to the new version automatically.
 */
define('MEDIA_23VIDEO_DATA_VERSION', 1);

/**
 * Wrapper for variable_get() that uses the Media: 23 Video variable registry.
 *
 * @param string $name
 *  The variable name to retrieve. Note that it will be namespaced by
 *  pre-pending MEDIA_23VIDEO_NAMESPACE, as to avoid variable collisions
 *  with other modules.
 * @param unknown $default
 *  An optional default variable to return if the variable hasn't been set
 *  yet. Note that within this module, all variables should already be set
 *  in the media_23video_variable_default() function.
 * @return unknown
 *  Returns the stored variable or its default.
 *
 * @see media_23video_variable_set()
 * @see media_23video_variable_del()
 * @see media_23video_variable_default()
 */
function media_23video_variable_get($name, $default = NULL) {
  // Allow for an override of the default.
  // Useful when a variable is required (like $path), but namespacing still desired.
  if (!isset($default)) {
    $default = media_23video_variable_default($name);
  }
  // Namespace all variables
  $variable_name = MEDIA_23VIDEO_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 * Wrapper for variable_set() that uses the Media: 23 Video variable registry.
 *
 * @param string $name
 *  The variable name to set. Note that it will be namespaced by
 *  pre-pending MEDIA_23VIDEO_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 * @param unknown $value
 *  The value for which to set the variable.
 * @return unknown
 *  Returns the stored variable after setting.
 *
 * @see media_23video_variable_get()
 * @see media_23video_variable_del()
 * @see media_23video_variable_default()
 */
function media_23video_variable_set($name, $value) {
  $variable_name = MEDIA_23VIDEO_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() that uses the Media: 23 Video variable registry.
 *
 * @param string $name
 *  The variable name to delete. Note that it will be namespaced by
 *  pre-pending MEDIA_23VIDEO_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 *
 * @see media_23video_variable_get()
 * @see media_23video_variable_set()
 * @see media_23video_variable_default()
 */
function media_23video_variable_del($name) {
  $variable_name = MEDIA_23VIDEO_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the Media: 23 Video namespace.
 *
 * @param string $name
 *  Optional variable name to retrieve the default. Note that it has not yet
 *  been pre-pended with the MEDIA_23VIDEO_NAMESPACE namespace at this time.
 * @return unknown
 *  The default value of this variable, if it's been set, or NULL, unless
 *  $name is NULL, in which case we return an array of all default values.
 *
 * @see media_23video_variable_get()
 * @see media_23video_variable_set()
 * @see media_23video_variable_del()
 */
function media_23video_variable_default($name = NULL) {
  static $defaults;

  if (!isset($defaults)) {
    $defaults = array(
      'domain' => 'reinvent.23video.com'
    );
  }

  if (!isset($name)) {
    return $defaults;
  }

  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

/**
 * Return the fully namespace variable name.
 *
 * @param string $name
 *  The variable name to retrieve the namespaced name.
 * @return string
 *  The fully namespace variable name, prepended with
 *  MEDIA_23VIDEO_NAMESPACE.
 */
function media_23video_variable_name($name) {
  return MEDIA_23VIDEO_NAMESPACE . $name;
}
