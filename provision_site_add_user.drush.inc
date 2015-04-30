<?php

/**
 * @file
 * Provision/Drush hooks for the provision-export_backup command.
 *
 * These are the hooks that will be executed by the drush_invoke function
 * when asking for an export backup command
 */

/**
 * Implements hook_drush_command().
 */
function provision_site_add_user_drush_command() {
  $items['provision-add_user'] = array(
    'description' => 'Add a user to a site and give them a role.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'name' => dt('User name'),
      'mail' => dt('E-mail address'),
      'role' => dt('Role'),
    ),
  );
  return $items;
}

/**
 * Map values of site node into command line arguments.
 */
/*function drush_provision_site_add_user_pre_hosting_task($task) {
  $task =& drush_get_context('HOSTING_TASK');

  // Pass the dialog entries to the drush provision script.
  if ($task->task_type == 'export_backup') {
    $task->args[1] = $task->task_args['backup'];
  }

  // Pass the task arguments to the drush provision script.
  if ($task->task_type == 'remove_export_backup') {
    $task->args[1] = $task->task_args['export'];
  }

}*/

/**
 * Implements drush_hook_COMMAND().
 */
function drush_provision_site_add_user_provision_add_user($name, $mail, $role) {
  drush_log(dt('Start add user command for '.$name), 'ok');

  provision_backend_invoke(d()->name, 'user-create', array($name), array('mail' => $mail));
  provision_backend_invoke(d()->name, 'user-add-role', array($role, $name));
  
drush_log(dt('Completed add user command for '.$name), 'ok');
}
