<?php

/**
 * @file
 */

/**
 * Implements of hook_drush_command().
 */
function rufe_drush_command() {
  $items = array();
  $items['remove-unavailable'] = array(
    'callback' => '_rufe',
    'description' => 'Delete unmanaged files from file_managed table.',
    'aliases' => array('rufe'),
    'examples' => array(
      'Remove unavailable file entires' => 'drush rufe',
    ),
  );
  return $items;
}

/**
 * Implements drush callback _rufe().
 */
function _rufe() {
  $query = db_select('file_managed', 'fm')->fields('fm', array('fid', 'uri'))->condition('status', 1, '=')->orderBy('fid', 'DESC')->execute()->fetchAllKeyed(0, 1);
  foreach ($query as $key => $value) {
    if (!file_exists($value)) {
      drush_print($value . ' with fid ' . $key . ' is getting deleted!');
      db_delete('file_managed')->condition('fid', $key, '=')->execute();
    }
    else {
      drush_print('Nothing to delete!');
      break;
    }
  }
}
