/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DefaultsParams.h
 * Author: root
 *
 * Created on 24 stycznia 2019, 22:11
 */

#ifndef DEFAULTSPARAMS_H
#define DEFAULTSPARAMS_H

#include <vector>
#include <string>

enum class DefaultsParams
{
    // Boolean
    BOOLEAN_START,
    always_query_group_plugin = BOOLEAN_START,
    always_set_home,
    authenticate,
    case_insensitive_group,
    case_insensitive_user,
    closefrom_override,
    compress_io,
    exec_background,
    env_editor,
    env_reset,
    fast_glob,
    fqdn,
    ignore_audit_errors,
    ignore_dot,
    ignore_iolog_errors,
    ignore_logfile_errors,
    ignore_local_sudoers,
    ignore_unknown_defaults,
    insults,
    log_host,
    log_input,
    log_output,
    log_year,
    long_otp_prompt,
    mail_all_cmnds,
    mail_always,
    mail_badpass,
    mail_no_host,
    mail_no_perms,
    mail_no_user,
    match_group_by_gid,
    netgroup_tuple,
    noexec,
    pam_session,
    pam_setcred,
    passprompt_override,
    path_info,
    preserve_groups,
    pwfeedback,
    requiretty,
    root_sudo,
    rootpw,
    runaspw,
    set_home,
    set_longname,
    set_utmp,
    setenv,
    shell_noargs,
    stay_setuid,
    sudoedit_checkdir,
    sudoedit_follow,
    syslog_pid,
    targetpw,
    tty_tickets,
    umask_override,
    use_loginclass,
    use_netgroups,
    use_pty,
    user_command_timeouts,
    utmp_runas,
    visiblepw,
    // Integers
    INTEGER_START,
    closeform = INTEGER_START,
    commant_timeout,
    maxseq,
    passwd_tries,
    syslog_maxlen,
    // Int-Boolean
    INT_BOOL_START,
    loglinelen = INT_BOOL_START,
    passwd_timeout,
    timestamp_timeout,
    umask,
    // Strings
    STRINGS_START,
    authfail_message = STRINGS_START,
    badpass_message,
    editor,
    iolog_dir,
    iolog_file,
    iolog_flush,
    iolog_group,
    iolog_mode,
    iolog_user,
    lecture_status_dir,
    limitprivs,
    mailsub,
    noexec_file,
    pam_login_service,
    pam_service,
    passprompt,
    privs,
    role,
    runas_default,
    sudoers_locale,
    timestamp_type,
    timestampdir,
    timestampowner,
    type,
    // Str-Bools
    STR_BOOL_START,
    env_file = STR_BOOL_START,
    exempt_group,
    fdexec,
    group_plugin,
    lecture,
    lecture_file,
    listpw,
    logfile,
    mailerflags,
    mailerpath,
    mailfrom,
    mailto,
    restricted_env_file,
    secure_path,
    syslog,
    syslog_badpri,
    syslog_goodpri,
    verifypw,
    // Lists-bool
    LIST_BOOL_START,
    env_check = LIST_BOOL_START,
    env_delete,
    env_keep,
    NUM_OF_PARAMS
};

const std::vector<std::string> g_DefaultsParamNames = 
{
    "always_query_group_plugin",
    "always_set_home",
    "authenticate",
    "case_insensitive_group",
    "case_insensitive_user",
    "closefrom_override",
    "compress_io",
    "exec_background",
    "env_editor",
    "env_reset",
    "fast_glob",
    "fqdn",
    "ignore_audit_errors",
    "ignore_dot",
    "ignore_iolog_errors",
    "ignore_logfile_errors",
    "ignore_local_sudoers",
    "ignore_unknown_defaults",
    "insults",
    "log_host",
    "log_input",
    "log_output",
    "log_year",
    "long_otp_prompt",
    "mail_all_cmnds",
    "mail_always",
    "mail_badpass",
    "mail_no_host",
    "mail_no_perms",
    "mail_no_user",
    "match_group_by_gid",
    "netgroup_tuple",
    "noexec",
    "pam_session",
    "pam_setcred",
    "passprompt_override",
    "path_info",
    "preserve_groups",
    "pwfeedback",
    "requiretty",
    "root_sudo",
    "rootpw",
    "runaspw",
    "set_home",
    "set_logname",
    "set_utmp",
    "setenv",
    "shell_noargs",
    "stay_setuid",
    "sudoedit_checkdir",
    "sudoedit_follow",
    "syslog_pid",
    "targetpw",
    "tty_tickets",
    "umask_override",
    "use_loginclass",
    "use_netgroups",
    "use_pty",
    "user_command_timeouts",
    "utmp_runas",
    "visiblepw",
    "closeform",
    "commant_timeout",
    "maxseq",
    "passwd_tries",
    "syslog_maxlen",
    "loglinelen",
    "passwd_timeout",
    "timestamp_timeout",
    "umask",
    "authfail_message",
    "badpass_message",
    "editor",
    "iolog_dir",
    "iolog_file",
    "iolog_flush",
    "iolog_group",
    "iolog_mode",
    "iolog_user",
    "lecture_status_dir",
    "limitprivs",
    "mailsub",
    "noexec_file",
    "pam_login_service",
    "pam_service",
    "passprompt",
    "privs",
    "role",
    "runas_default",
    "sudoers_locale",
    "timestamp_type",
    "timestampdir",
    "timestampowner",
    "type",
    "env_file",
    "exempt_group",
    "fdexec",
    "group_plugin",
    "lecture",
    "lecture_file",
    "listpw",
    "logfile",
    "mailerflags",
    "mailerpath",
    "mailfrom",
    "mailto",
    "restricted_env_file",
    "secure_path",
    "syslog",
    "syslog_badpri",
    "syslog_goodpri",
    "verifypw",
    "env_check",
    "env_delete",
    "env_keep"
};

inline 
DefaultsParams GetParamFromName(std::string name)
{
    for(long i = 0; i < g_DefaultsParamNames.size(); i++)
    {
        if (g_DefaultsParamNames[i] == name)
        {
            return static_cast<DefaultsParams>(i);
        }
    }
    
    return DefaultsParams::NUM_OF_PARAMS;
}



#endif /* DEFAULTSPARAMS_H */

