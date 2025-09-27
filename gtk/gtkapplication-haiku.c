/*
 * Copyright © 2010 Codethink Limited
 * Copyright © 2013 Canonical Limited
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the licence, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Ryan Lortie <desrt@desrt.ca>
 */

#include "config.h"

#include "gtkapplicationprivate.h"
#include "gtkbuilder.h"
//#import <Cocoa/Cocoa.h>

typedef struct
{
  guint cookie;
  GtkApplicationInhibitFlags flags;
  char *reason;
  GtkWindow *window;
} GtkApplicationHaikuInhibitor;

static void
gtk_application_haiku_inhibitor_free (GtkApplicationHaikuInhibitor *inhibitor)
{
  g_free (inhibitor->reason);
  g_clear_object (&inhibitor->window);
  g_slice_free (GtkApplicationHaikuInhibitor, inhibitor);
}

typedef GtkApplicationImplClass GtkApplicationImplHaikuClass;

typedef struct
{
  GtkApplicationImpl impl;

  GtkActionMuxer *muxer;
  GMenu *combined;

  GSList *inhibitors;
  gint quit_inhibit;
  guint next_cookie;
//  NSObject *delegate;
} GtkApplicationImplHaiku;

G_DEFINE_TYPE (GtkApplicationImplHaiku, gtk_application_impl_haiku, GTK_TYPE_APPLICATION_IMPL)

#if 0
#if MAC_OS_X_VERSION_MIN_REQUIRED >= 1060
@interface GtkApplicationHaikuDelegate : NSObject <NSApplicationDelegate>
#else
@interface GtkApplicationHaikuDelegate : NSObject
#endif
{
  GtkApplicationImplHaiku *haiku;
}

- (id)initWithImpl:(GtkApplicationImplHaiku*)impl;
- (NSApplicationTerminateReply) applicationShouldTerminate:(NSApplication *)sender;
- (void)application:(NSApplication *)theApplication openFiles:(NSArray *)filenames;
- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app;
@end

@implementation GtkApplicationHaikuDelegate
-(id)initWithImpl:(GtkApplicationImplHaiku*)impl
{
  [super init];
  haiku = impl;
  return self;
}

-(NSApplicationTerminateReply) applicationShouldTerminate:(NSApplication *)sender
{
  const gchar *quit_action_name = "quit";
  GActionGroup *action_group = G_ACTION_GROUP (haiku->impl.application);

  if (haiku->quit_inhibit != 0)
    return NSTerminateCancel;

  if (g_action_group_has_action (action_group, quit_action_name))
    {
      g_action_group_activate_action (action_group, quit_action_name, NULL);
      return NSTerminateCancel;
    }

  return NSTerminateNow;
}

-(void)application:(NSApplication *)theApplication openFiles:(NSArray *)filenames
{
  GFile **files;
  gint i;
  GApplicationFlags flags;

  flags = g_application_get_flags (G_APPLICATION (haiku->impl.application));

  if (~flags & G_APPLICATION_HANDLES_OPEN)
    {
      [theApplication replyToOpenOrPrint:NSApplicationDelegateReplyFailure];
      return;
    }

  files = g_new (GFile *, [filenames count]);

  for (i = 0; i < [filenames count]; i++)
    files[i] = g_file_new_for_path ([(NSString *)[filenames objectAtIndex:i] UTF8String]);

  g_application_open (G_APPLICATION (haiku->impl.application), files, [filenames count], "");

  for (i = 0; i < [filenames count]; i++)
    g_object_unref (files[i]);

  g_free (files);

  [theApplication replyToOpenOrPrint:NSApplicationDelegateReplySuccess];
}

-(BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app
{
  return YES;
}
@end
#endif

/* these exist only for accel handling */
static void
gtk_application_impl_haiku_hide (GSimpleAction *action,
                                  GVariant      *parameter,
                                  gpointer       user_data)
{
#if 0
  [NSApp hide:NSApp];
#endif
}

static void
gtk_application_impl_haiku_hide_others (GSimpleAction *action,
                                         GVariant      *parameter,
                                         gpointer       user_data)
{
#if 0
  [NSApp hideOtherApplications:NSApp];
#endif
}

static void
gtk_application_impl_haiku_show_all (GSimpleAction *action,
                                      GVariant      *parameter,
                                      gpointer       user_data)
{
#if 0
  [NSApp unhideAllApplications:NSApp];
#endif
}

static GActionEntry gtk_application_impl_haiku_actions[] = {
  { "hide",             gtk_application_impl_haiku_hide        },
  { "hide-others",      gtk_application_impl_haiku_hide_others },
  { "show-all",         gtk_application_impl_haiku_show_all    }
};

static void
gtk_application_impl_haiku_startup (GtkApplicationImpl *impl,
                                     gboolean            register_session)
{
#if 0
  GtkApplicationImplHaiku *haiku = (GtkApplicationImplHaiku *) impl;
  GSimpleActionGroup *gtkinternal;
  GMenuModel *app_menu;
  const gchar *pref_accel[] = {"<Primary>comma", NULL};
  const gchar *hide_others_accel[] = {"<Primary><Alt>h", NULL};
  const gchar *hide_accel[] = {"<Primary>h", NULL};
  const gchar *quit_accel[] = {"<Primary>q", NULL};

  if (register_session)
    {
      haiku->delegate = [[GtkApplicationHaikuDelegate alloc] initWithImpl:haiku];
      [NSApp setDelegate: (id)(haiku->delegate)];
    }

  haiku->muxer = gtk_action_muxer_new ();
  gtk_action_muxer_set_parent (haiku->muxer, gtk_application_get_action_muxer (impl->application));

  /* Add the default accels */
  gtk_application_set_accels_for_action (impl->application, "app.preferences", pref_accel);
  gtk_application_set_accels_for_action (impl->application, "gtkinternal.hide-others", hide_others_accel);
  gtk_application_set_accels_for_action (impl->application, "gtkinternal.hide", hide_accel);
  gtk_application_set_accels_for_action (impl->application, "app.quit", quit_accel);

  /* and put code behind the 'special' accels */
  gtkinternal = g_simple_action_group_new ();
  g_action_map_add_action_entries (G_ACTION_MAP (gtkinternal), gtk_application_impl_haiku_actions,
                                   G_N_ELEMENTS (gtk_application_impl_haiku_actions), haiku);
  gtk_application_insert_action_group (impl->application, "gtkinternal", G_ACTION_GROUP (gtkinternal));
  g_object_unref (gtkinternal);

  /* now setup the menu */
  app_menu = gtk_application_get_app_menu (impl->application);
  if (app_menu == NULL)
    {
      GtkBuilder *builder;

      /* If the user didn't fill in their own menu yet, add ours.
       *
       * The fact that we do this here ensures that we will always have the
       * app menu at index 0 in 'combined'.
       */
      builder = gtk_builder_new_from_resource ("/org/gtk/libgtk/ui/gtkapplication-haiku.ui");
      gtk_application_set_app_menu (impl->application, G_MENU_MODEL (gtk_builder_get_object (builder, "app-menu")));
      g_object_unref (builder);
    }
  else
    gtk_application_impl_set_app_menu (impl, app_menu);

  /* This may or may not add an item to 'combined' */
  gtk_application_impl_set_menubar (impl, gtk_application_get_menubar (impl->application));

  /* OK.  Now put it in the menu. */
  gtk_application_impl_haiku_setup_menu (G_MENU_MODEL (haiku->combined), haiku->muxer);

  [NSApp finishLaunching];
#endif
}

static void
gtk_application_impl_haiku_shutdown (GtkApplicationImpl *impl)
{
#if 0
  GtkApplicationImplHaiku *haiku = (GtkApplicationImplHaiku *) impl;

  /* destroy our custom menubar */
  [NSApp setMainMenu:[[[NSMenu alloc] init] autorelease]];

  if (haiku->delegate)
    {
      [haiku->delegate release];
      haiku->delegate = NULL;
    }

  g_slist_free_full (haiku->inhibitors, (GDestroyNotify) gtk_application_haiku_inhibitor_free);
  haiku->inhibitors = NULL;
#endif
}

static void
gtk_application_impl_haiku_active_window_changed (GtkApplicationImpl *impl,
                                                   GtkWindow          *window)
{
  GtkApplicationImplHaiku *haiku = (GtkApplicationImplHaiku *) impl;

  gtk_action_muxer_remove (haiku->muxer, "win");

  if (G_IS_ACTION_GROUP (window))
    gtk_action_muxer_insert (haiku->muxer, "win", G_ACTION_GROUP (window));
}

static void
gtk_application_impl_haiku_set_app_menu (GtkApplicationImpl *impl,
                                          GMenuModel         *app_menu)
{
  GtkApplicationImplHaiku *haiku = (GtkApplicationImplHaiku *) impl;

  /* If there are any items at all, then the first one is the app menu */
  if (g_menu_model_get_n_items (G_MENU_MODEL (haiku->combined)))
    g_menu_remove (haiku->combined, 0);

  if (app_menu)
    g_menu_prepend_submenu (haiku->combined, "Application", app_menu);
  else
    {
      GMenu *empty;

      /* We must preserve the rule that index 0 is the app menu */
      empty = g_menu_new ();
      g_menu_prepend_submenu (haiku->combined, "Application", G_MENU_MODEL (empty));
      g_object_unref (empty);
    }
}

static void
gtk_application_impl_haiku_set_menubar (GtkApplicationImpl *impl,
                                         GMenuModel         *menubar)
{
  GtkApplicationImplHaiku *haiku = (GtkApplicationImplHaiku *) impl;

  /* If we have the menubar, it is a section at index '1' */
  if (g_menu_model_get_n_items (G_MENU_MODEL (haiku->combined)) > 1)
    g_menu_remove (haiku->combined, 1);

  if (menubar)
    g_menu_append_section (haiku->combined, NULL, menubar);
}

static guint
gtk_application_impl_haiku_inhibit (GtkApplicationImpl         *impl,
                                     GtkWindow                  *window,
                                     GtkApplicationInhibitFlags  flags,
                                     const gchar                *reason)
{
  GtkApplicationImplHaiku *haiku = (GtkApplicationImplHaiku *) impl;
  GtkApplicationHaikuInhibitor *inhibitor;

  inhibitor = g_slice_new (GtkApplicationHaikuInhibitor);
  inhibitor->cookie = ++haiku->next_cookie;
  inhibitor->flags = flags;
  inhibitor->reason = g_strdup (reason);
  inhibitor->window = window ? g_object_ref (window) : NULL;

  haiku->inhibitors = g_slist_prepend (haiku->inhibitors, inhibitor);

  if (flags & GTK_APPLICATION_INHIBIT_LOGOUT)
    haiku->quit_inhibit++;

  return inhibitor->cookie;
}

static void
gtk_application_impl_haiku_uninhibit (GtkApplicationImpl *impl,
                                       guint               cookie)
{
  GtkApplicationImplHaiku *haiku = (GtkApplicationImplHaiku *) impl;
  GSList *iter;

  for (iter = haiku->inhibitors; iter; iter = iter->next)
    {
      GtkApplicationHaikuInhibitor *inhibitor = iter->data;

      if (inhibitor->cookie == cookie)
        {
          if (inhibitor->flags & GTK_APPLICATION_INHIBIT_LOGOUT)
            haiku->quit_inhibit--;
          gtk_application_haiku_inhibitor_free (inhibitor);
          haiku->inhibitors = g_slist_delete_link (haiku->inhibitors, iter);
          return;
        }
    }

  g_warning ("Invalid inhibitor cookie");
}

static gboolean
gtk_application_impl_haiku_is_inhibited (GtkApplicationImpl         *impl,
                                          GtkApplicationInhibitFlags  flags)
{
  GtkApplicationImplHaiku *haiku = (GtkApplicationImplHaiku *) impl;

  if (flags & GTK_APPLICATION_INHIBIT_LOGOUT)
    return haiku->quit_inhibit > 0;

  return FALSE;
}

static void
gtk_application_impl_haiku_init (GtkApplicationImplHaiku *haiku)
{
#if 0
  /* This is required so that Cocoa is not going to parse the
     command line arguments by itself and generate OpenFile events.
     We already parse the command line ourselves, so this is needed
     to prevent opening files twice, etc. */
  [[NSUserDefaults standardUserDefaults] setObject:@"NO"
                                            forKey:@"NSTreatUnknownArgumentsAsOpen"];

  haiku->combined = g_menu_new ();
#endif
}

static void
gtk_application_impl_haiku_finalize (GObject *object)
{
  GtkApplicationImplHaiku *haiku = (GtkApplicationImplHaiku *) object;

  g_clear_object (&haiku->combined);

  G_OBJECT_CLASS (gtk_application_impl_haiku_parent_class)->finalize (object);
}

static void
gtk_application_impl_haiku_class_init (GtkApplicationImplClass *class)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (class);

  class->startup = gtk_application_impl_haiku_startup;
  class->shutdown = gtk_application_impl_haiku_shutdown;
  class->active_window_changed = gtk_application_impl_haiku_active_window_changed;
  class->set_app_menu = gtk_application_impl_haiku_set_app_menu;
  class->set_menubar = gtk_application_impl_haiku_set_menubar;
  class->inhibit = gtk_application_impl_haiku_inhibit;
  class->uninhibit = gtk_application_impl_haiku_uninhibit;
  class->is_inhibited = gtk_application_impl_haiku_is_inhibited;

  gobject_class->finalize = gtk_application_impl_haiku_finalize;
}
