#!/usr/bin/gjs

const Gdk = imports.gi.Gdk;
const Gio = imports.gi.Gio;
const GLib = imports.gi.GLib;
const Gtk = imports.gi.Gtk;
const Lang = imports.lang;

const Application = new Lang.Class({
    Name: 'Application',

    //create the application
    _init: function() {
        this.application = new Gtk.Application({
            application_id: 'org.example.myapp',
            flags: Gio.ApplicationFlags.FLAGS_NONE
        });

       //connect to 'activate' and 'startup' signals to the callback functions
       this.application.connect('activate', Lang.bind(this, this._onActivate));
       this.application.connect('startup', Lang.bind(this, this._onStartup));
    },

    //create the UI (in this case it's just the ApplicationWindow
    _buildUI: function() {
        this._window = new Gtk.ApplicationWindow({ application: this.application,
                                                   window_position: Gtk.WindowPosition.CENTER,
                                                   title: "Toolbar Example",
                                                   default_height: 200,
                                                   default_width: 400 });

        this._grid = new Gtk.Grid();
        this._window.add(this._grid);
        this._grid.show();

        this._createToolbar();
        this._toolbar.set_hexpand(true);
        this._grid.attach(this._toolbar, 0, 0, 1, 1);

        //show the  toolbar and window
        this._toolbar.show();
        this._window.show();
    },

    //callback function for 'activate' signal
    _onActivate: function() {
        this._window.present();
    },

    //callback function for 'startup' signal
    _onStartup: function() {
        this._initMenus();
        this._buildUI();
    },

    //create the toolbar, its toolbuttons and their actions
    _createToolbar: function() {

        this._toolbar = new Gtk.Toolbar();
        this._toolbar.get_style_context().add_class(Gtk.STYLE_CLASS_PRIMARY_TOOLBAR);

        //create the "New" ToolButton and its SimpleAction.
        //Using actions allows you to add them to the app menu
        //without duplicating code.
        let newAction = new Gio.SimpleAction({ name: 'new'});
        newAction.connect('activate', Lang.bind(this,
            function() {
                this._newCB();
            }));
        this.application.add_action(newAction);//note: this action is added to the app

        this._newButton = new Gtk.ToolButton.new_from_stock(Gtk.STOCK_NEW);
        this._newButton.is_important = true;
        this._toolbar.add(this._newButton);
        this._newButton.show();
        this._newButton.action_name = "app.new";

        //create the "Open" ToolButton and its SimpleAction
        let openAction = new Gio.SimpleAction({ name: 'open'});
        openAction.connect('activate', Lang.bind(this,
            function() {
                this._openCB();
            }));
        this.application.add_action(openAction);

        this._openButton = new Gtk.ToolButton.new_from_stock(Gtk.STOCK_OPEN);
        this._openButton.is_important = true;
        this._toolbar.add(this._openButton);
        this._openButton.show();
        this._openButton.action_name = "app.open";

        //create the "Undo" ToolButton and its SimpleAction
        let undoAction = new Gio.SimpleAction({ name: 'undo'});
        undoAction.connect('activate', Lang.bind (this,
            function() {
                this._undoCB();
            }));
        this._window.add_action(undoAction);//note this action is added to the window

        this._undoButton = new Gtk.ToolButton.new_from_stock(Gtk.STOCK_UNDO);
        this._undoButton.is_important = true;
        this._toolbar.add(this._undoButton);
        this._undoButton.show();
        this._undoButton.action_name = "win.undo";

        //create the "Fullscreen" ToolButton and its SimpleAction
        let fullscreenToggleAction = new Gio.SimpleAction ({ name: 'fullscreenToggle' });
        fullscreenToggleAction.connect ('activate', Lang.bind (this,
            function () {
                this._fullscreenToggleCB();
            }));
        this._window.add_action(fullscreenToggleAction);

        this._fullscreenButton = new Gtk.ToolButton.new_from_stock(Gtk.STOCK_FULLSCREEN);
        this._fullscreenButton.is_important = true;
        this._toolbar.add(this._fullscreenButton);
        this._fullscreenButton.show();
        this._fullscreenButton.action_name = "win.fullscreenToggle";

        //create the "leaveFullscreen" ToolButton, and set the action name to "win.fullscreenToggle"
        this._leaveFullscreenButton = new Gtk.ToolButton.new_from_stock(Gtk.STOCK_LEAVE_FULLSCREEN);
        this._leaveFullscreenButton.is_important = true;
        this._toolbar.add(this._leaveFullscreenButton);
        this._leaveFullscreenButton.action_name = "win.fullscreenToggle";
    },

    _initMenus: function () {
        let menu = new Gio.Menu();
        menu.append("New", 'app.new');
        menu.append("Open", 'app.open');
        menu.append("Quit", 'app.quit');

        this.application.set_app_menu(menu);

        let quitAction = new Gio.SimpleAction({name: 'quit' });
        quitAction.connect('activate', Lang.bind(this,
            function() {
                this._window.destroy();
            }));
        this.application.add_action(quitAction);
    },

    _newCB: function() {
        print("You clicked 'New'.");
    },

    _openCB: function() {
        print("You clicked 'Open'.");
    },

    _undoCB:function () {
        print ("You clicked 'Undo'.");
    },

    _fullscreenToggleCB: function() {
        if ((this._window.get_window().get_state() & Gdk.WindowState.FULLSCREEN) != 0 ) {
              this._window.unfullscreen();
              this._leaveFullscreenButton.hide();
              this._fullscreenButton.show();
        }
        else {
             this._window.fullscreen();
             this._fullscreenButton.hide();
             this._leaveFullscreenButton.show();
        }
    }
});

//run the application
let app = new Application();
app.application.run(ARGV);