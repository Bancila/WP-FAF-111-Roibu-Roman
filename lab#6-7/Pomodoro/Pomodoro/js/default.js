// For an introduction to the Blank template, see the following documentation:
// http://go.microsoft.com/fwlink/?LinkId=232509

var sessionCount = 1;
var sessionLength = 25;
var running = false;
var minutes;
var seconds;

function update() {
    if (!running) return;
    else if ((seconds == 0) && (minutes == 0)) {
        var messageBox = new Windows.UI.Popups.MessageDialog("Hurray! You've completed yet another Pomodoro! Go celebrate with a beaverage, and see you soon.", "Pomodoro Complete!");
        messageBox.showAsync();
        document.getElementById("success-sound").play();
        setSessionMinutes();
        enableAndDisableButtons();
        sessionCount++;
        updateSessionCounterLabel();
        return;
    }
    else {
        if (seconds == 0) {
            seconds = 60;
            minutes--;
        }
        seconds--;
        updateTimeLabel();
        setTimeout(update, 1000);
    }
}

function startButtonClickHandler(eventInfo) {
    document.getElementById("success-sound").play();
    enableAndDisableButtons();
    setTimeout(update, 1000);
}

function stopButtonClickHandler(eventInfo) {
    var msgpopup = new Windows.UI.Popups.MessageDialog("Whoops! It seems that you've stoped a Pomodoro. You shouldn't do that. No cookie for you!", "Pomodoro Stoped!");
    msgpopup.showAsync();
    document.getElementById("fail-sound").play();
    enableAndDisableButtons();
    setSessionMinutes();
}

function setSessionMinutes() {
    var e = document.getElementById("sessionSelect");
    minutes = e.options[e.selectedIndex].value;
    seconds = 0;
    updateTimeLabel();
}

function updateTimeLabel() {
    var minLabel = "" + minutes;
    var secLabel = "" + seconds;
    // Correct for leading zeros
    if (minutes < 10) minLabel = "0" + minLabel;
    if (seconds < 10) secLabel = "0" + secLabel;
    document.getElementById("sessionTime").innerHTML = minLabel + ':' + secLabel;
}

function updateSessionCounterLabel() {
    document.getElementById("sessionCounter").innerHTML = "Session " + sessionCount;
}

function enableAndDisableButtons() {
    if (running) {
        running = false;
        document.getElementById("sessionSelect").disabled = false;
        document.getElementById("startButton").disabled = false;
        document.getElementById("stopButton").disabled = true;
    }
    else {
        running = true;
        document.getElementById("sessionSelect").disabled = true;
        document.getElementById("startButton").disabled = true;
        document.getElementById("stopButton").disabled = false;
    }
}

(function () {
    "use strict";

    WinJS.Binding.optimizeBindingReferences = true;

    var app = WinJS.Application;
    var activation = Windows.ApplicationModel.Activation;

    app.onactivated = function (args) {
        if (args.detail.kind === activation.ActivationKind.launch) {
            if (args.detail.previousExecutionState !== activation.ApplicationExecutionState.terminated) {
                // Initialize your application here.
                document.getElementById("stopButton").disabled = true;
                updateSessionCounterLabel();
                setSessionMinutes();
            } else {
                // Restore application state here.
                updateTimeLabel();
            }
            args.setPromise(WinJS.UI.processAll());
        }
    };

    app.oncheckpoint = function (args) {
        // TODO: This application is about to be suspended. Save any state
        // that needs to persist across suspensions here. You might use the
        // WinJS.Application.sessionState object, which is automatically
        // saved and restored across suspension. If you need to complete an
        // asynchronous operation before your application is suspended, call
        // args.setPromise().
    };

    app.start();
})();
