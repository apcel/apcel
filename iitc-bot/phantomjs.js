"use strict";

var system = require('system'),
    address = "https://ingress.com/intel",
    page = require('webpage').create(),
    loadInProgress = false,
    testReady = true,
    found, testindex = 0,
    fs = require('fs'),
    google_email,
    google_password,
    startDate = new Date().getTime(),
    oldSettings, newSettings,
    jsonSettingsFile = "secure/jsonSettingsFile.json";

page.loadInProgress = false;

function rasterize(page) {
    var n = new Date().getTime();
    var output = "debug.png";
    shot(page, "phantomjs_" + n.toString() + "_" + output);
};

function shot(page, fname) {
    page.render(fname);
};
page.onConsoleMessage = function(msg) {
    console.log(msg);
};
page.onLoadStarted = function() {
    page.loadInProgress = true;
};
page.onLoadFinished = function() {
    page.loadInProgress = false;
};
page.onError = function() {
    rasterize(page);
};
var steps = [
    function() { //1. Get url to go
        testReady = false;
        page.open(address, function(status) {
            if (status !== 'success') {
                console.log('Unable to load the address! ' + address);
                phantom.exit(1);
            } else {
                found = page.evaluate(function() {
                    var temp = document.links;
                    for (var i = 0; i < temp.length; i++) {
                        if (temp[i].href.toString().indexOf("ServiceLogin") > 0) {
                            return temp[i].href.toString();
                        };
                    };
                });
            };
        });
        testReady = true;
    },
    function() { //2. Go there
        testReady = false;
        page.open(found, function(status) {
            if (status !== 'success') {
                console.log('Unable to load the address! ' + found);
                phantom.exit(1);
            };
        });
        testReady = true;
    },

    function() { //3. Type email
        testReady = false;
        page.evaluate(function(google_email) {
            document.getElementById("Email").value = google_email;

        }, google_email);
        testReady = true;
    },
    function() { //4. Click "next"
        testReady = false;
        page.evaluate(function() {
            var ev = document.createEvent('MouseEvent');
            ev.initMouseEvent('click', true, true, window, null, 0, 0, 0, 0, false, false, false, false, 0, null);
            document.getElementById("next").dispatchEvent(ev);
        });
        testReady = true;
    },
    function() { //5. Type password
        testReady = false;
        page.evaluate(function(google_password) {
            document.getElementById("Passwd").value = google_password;
        }, google_password);
        testReady = true;
    },
    function() { //6. Click "sign in"
        testReady = false;
        page.evaluate(function() {
            var ev = document.createEvent('MouseEvent');
            ev.initMouseEvent('click', true, true, window, null, 0, 0, 0, 0, false, false, false, false, 0, null);
            document.getElementById("signIn").dispatchEvent(ev);
        });
        testReady = true;
    },

    function() { //7. Save cookies for ingress
        testReady = false;
        var allCookies = page.cookies
        var tempCookies = {};
        for (var i = 0; i < allCookies.length; i++) {
            tempCookies[allCookies[i].name] = allCookies[i].value;
            if (allCookies[i].name === "SACSID")
                tempCookies.expires = allCookies[i].expires
        };
        newSettings.cookieSACSID = tempCookies["SACSID"];
        newSettings.CSRF = tempCookies["csrftoken"];
        newSettings.expires = tempCookies.expires;
        testReady = true;
    },
    function() { //8. Save all cookies to file
        fs.write(jsonSettingsFile, JSON.stringify(newSettings, null, '\t'), "w");
    }
];
/*************************************************************************************/
var tmp = fs.read(jsonSettingsFile);
eval("oldSettings = " + tmp);
newSettings = oldSettings;
google_password = oldSettings.google_password;
google_email = oldSettings.google_email;

if ((typeof(oldSettings) != "object") || (google_password === undefined) || (google_email === undefined)) {
    console.error('You must specify a json object containing at least' +
        ' "google_email" and "google_password" variables in file "' + jsonSettingsFile +'"');
    phantom.exit();
}

var loginLoop = setInterval(function() {
    if (testReady && typeof steps[testindex] != "function") {
        console.log('')
        console.log("Login complete!");
        phantom.exit();
    } else
    if (!page.loadInProgress && testReady) {
        steps[testindex]();
        testindex++;
        // window.setTimeout(shot(page, "phantom_" + startDate + "_step_" + testindex + ".png"), 50);
        fs.write('/dev/stderr', 'V', 'w');
    } else
        fs.write('/dev/stderr', '.', 'w');
}, 2000);