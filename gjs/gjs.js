#!/usr/bin/gjs

const Gio = imports.gi.Gio;
const GLib = imports.gi.GLib;
const Gtk = imports.gi.Gtk;
const Lang = imports.lang;

const Application = new Lang.Class ({
    Name: 'Application',

    //create the application
    _init: function () {
        this.application = new Gtk.Application ({
            application_id: 'org.example.myapp',
            flags: Gio.ApplicationFlags.FLAGS_NONE
        });

       this.application.connect('activate', Lang.bind(this, this._onActivate));
    },

    //callback function for 'activate' signal
    _onActivate: function () {

        MyWindow = new Gtk.Window({type: Gtk.WindowType.TOPLEVEL});
        MyWindow.title = "Welcome to GNOME";

       /* Here are a few ways we can customize our window.
       Try uncommenting them or changing their values! */
        //MyWindow.set_default_size (400,200);
        //MyWindow.set_has_resize_grip (false);
        //MyWindow.set_opacity (0.5);
        //MyWindow.maximize ();

        //show the window and all child widgets (none in this case)
        MyWindow.show_all();
        this.application.add_window(MyWindow);
    }
});

//run the application
let app = new Application ();
app.application.run (ARGV);