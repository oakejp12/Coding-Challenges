/**
 * Created by oakesjo on 7/22/2014.
 */

/*
 *  Reads file from the links via AJAX
 *  Either calls callback function or displays error message.
 *  AJAX: Asynchronous JavaScript and XML
 */



var jqxhr = function (path) {

    $.ajax({

        cache: false,
        type: "GET", // Default -> Don't have to add in
        contentType: "multipart/form-data",
        url: path,
        statusCode: {
          404: function(){
              $("#writeHere").text("Log file not found!");
          }
        },
        success: function (res) { // If AJAX req is successful, res is the data
            console.log("AJAX Success!");
            callback(res);

        },
        error: function (err) { //log the error and alert the user
            console.log("ERROR: ", err);
            $("#writeHere").html("There was an error in reading the file.");
            $('#showLog').html("");
        },
        beforeSend: function () { //before sending to callback function
            $("#writeHere").text("Reading..");
            $("showLog").text("");
        },
        complete: function () { // When AJAX Processing is complete, invoked after the callback
            console.log("Complete invoked.");
            console.log("-------------------")
        }
    });
};

/*
 *  Callback function is invoked when the log file is read successfully!
 *  Used to process and output the errors in the log file!
 */

var callback = function (res) {

    console.log("In callback");

    //jQuery variables for id's in HTML
    var $summary = $("#writeHere");
    var $showLog = $("#showLog");

    var count = res.match(/(\sERROR\s)/gm); // Counts the number of errors in the log file
    var countSevere = res.match(/(^SEVERE:)/gm); // Used for the catalina/localhost log files


    var revlocal = ((res).split("\n").reverse().join("\n")); // For the localhost and catalina log files


    var reDiaBtoa = /^(\[[^\]]*\]) (\w+?) (\[[^\]]*\]) (\([^)]*\)) (.*)$/gm; //diamond.log, btoa_app log files
    var reBSF = /^([^a-z]*) (\w+?) ([^\(]*)(\([^)]*\)) (\[[^\]]*\]) (.*)$/gm; //matches the bsf.log file
    var reRESP = /^([^a-z]*) (\[[^\]]*\]) (\w+?) ([^\-]*) ([^a-z]) (.*)$/gm; //matches the response_errors.log file
    var reREVlocCat = /^([a-zA-Z]*): (.*)(?:\s)([^co]+) ([^\s]+) (\w*)$/gm; //matches localhost and catalina log files

    var match; // array for the regex exec function
    var outputToDisplay = " "; // Outputs the errors to the html page
    var errCount = 0; // Used to count how many errors need to be outputted


    // Used to put the file into an array by lines, so I can reverse it and get the N most recent erros
    var array = res.toString().split('\n');
    var newArray = array.reverse();

    if (reDiaBtoa.test(res) || reBSF.test(res) || reRESP.test(res)) {

        // If there are no errors in the log file
        if (count === null) {

            $summary.text("There are no errors in the log file!");
            $showLog.text("");

        }

        else {


            var num = prompt("How many messages do you want to see of the " + count.length + " error messages?");

            console.time("Time DiaBtoa, reBSF, reRESP");

            if (num > count.length) {
                num = count.length;
                console.log("Prompted number reset to: " + num);
            }


            /*
             * Process errors if regex matches the Diamond.log and btoa_app.log files
             */
            if (reDiaBtoa.test(res)) {

                console.log("Running reDiaBtoa");

                for (var j = 0, k = newArray.length; j <= k; j++) { // Since newArray[0] contains an empty string

                    while ((match = reDiaBtoa.exec(newArray[j])) != null) {


                        if (match.index === reDiaBtoa.lastIndex) {
                            reDiaBtoa.lastIndex++;
                        }

                        if (match[2] === "ERROR" && errCount < num) {

                            errCount++;

                            outputToDisplay += "<strong id='errCount'>" + "Error: " + "</strong>" + errCount + "<br/>" +
                                "<strong >" + "Time: " + "</strong>" + match[1] +
                                "<br/>" + "<strong>" + "Thread Name: " + "</strong>" + match[3] +
                                "<br/>" + "<strong>" + "Source name & line number: " + "</strong>" + match[4] +
                                "<br/>" + "<strong>" + "Log Message: " + "</strong>" + match[5] +
                                "<br/><br/>" + "<hr>" + "<br/>";

                        }
                    }
                }
                //Output the ERROR messages onto the HTML page
                document.getElementById("writeHere").innerHTML = outputToDisplay;
            }

            /*
             *  Process errors if regex matches the bsf.log files
             */
            else if (reBSF.test(res)) {

                console.log("Running reBSF");

                for (j = -1, k = newArray.length + 1; j <= k; j++) { // Since newArray[0] contains an empty string

                    // While loop runs through the document and matches lines in which there exists                    ERROR messages
                    while ((match = reBSF.exec(newArray[j])) != null) {

                        if (match.index === reBSF.lastIndex) {
                            reBSF.lastIndex++;
                        }

                        if (match[2] === "ERROR" && errCount < num) {

                            errCount++;

                            // Summary of the ERROR log messages
                            //TODO: Find the other important information
                            outputToDisplay += "<strong id='errCount'>" + "Error: " + "</strong>" + errCount + "<br/>" +
                                "<strong >" + "Time: " + "</strong>" + match[1] +
                                "<br/>" + "<strong>" + "Thread Name: " + "</strong>" + match[5] +
                                "<br/>" + "<strong>" + "Source name & line number: " + "</strong>" + match[4] +
                                "<br/>" + "<strong>" + "Log Message: " + "</strong>" + match[6] +
                                "<br/><br/>" + "<hr>" + "<br/>";

                        }
                    }
                }
                //Output the ERROR messages onto the HTML page
                document.getElementById("writeHere").innerHTML = outputToDisplay;
            }

            else if (reRESP.test(res)) {

                console.log("Running reRESP");

                for (j = -1, k = newArray.length; j <= k; j++) {

                    // While loop runs through the document and matches lines in which there exists                    ERROR messages
                    while ((match = reRESP.exec(newArray[j])) != null) {

                        if (match.index === reRESP.lastIndex) {
                            reRESP.lastIndex++;
                        }

                        if (match[3] === "ERROR" && errCount < num) {

                            errCount++;

                            outputToDisplay += "<strong id='errCount'>" + "Error: " + "</strong>" + errCount + "<br/>" +
                                "<strong >" + "Time: " + "</strong>" + match[1] +
                                "<br/>" + "<strong>" + "Thread Name: " + "</strong>" + match[2] +
                                "<br/>" + "<strong>" + "Source name & line number: " + "</strong>" + match[4] +
                                "<br/>" + "<strong>" + "Log Message: " + "</strong>" + match[6] +
                                "<br/><br/>" + "<hr>" + "<br/>";
                        }
                    }
                }

                //Output the ERROR messages onto the HTML page
                document.getElementById("writeHere").innerHTML = outputToDisplay;
            }
        }
    }

    else if (reREVlocCat.test(revlocal)) {


        console.log("Running relocCat ");

        if (countSevere === null) {

            $summary.text("There are no errors in the log file!");
            $showLog.text("");

        }

        else {

            /*
             * Reason why there are two regex and res instances:
             *  - Regex: As with exec (or in combination with it), test called multiple times on
             * the same global regular expression instance will advance past the previous match.
             */

            var relocalHostCat = /^([a-zA-Z]*): (.*)(?:\s)([^co]+) ([^\s]+) (\w*)$/gm, localcat = ((res).split("\n").reverse().join("\n"));

            console.log("Counted SEVERE errors: " + countSevere.length);

            num = prompt("How many messages do you want to view of the " + countSevere.length + " severe messages?");
            console.time("Time locCat");

            // If the user input is higher than the actual errors, reset user input to number of errors
            if (num > countSevere.length) {

                num = countSevere.length;
                console.log("Num reset to: " + num);
            }

            while ((match = relocalHostCat.exec(localcat)) !== null) {


                if (match[1] === "SEVERE" && errCount < num) {

                    errCount++;

                    outputToDisplay += "<strong id='errCount'>" + "Error: " + "</strong>" + errCount + "<br/>" +
                        "<strong >" + "Time: " + "</strong>" + match[3] +
                        "<br/>" + "<strong>" + "Status: " + "</strong>" + match[5] +
                        "<br/>" + "<strong>" + "Host: " + "</strong>" + match[4] +
                        "<br/>" + "<strong>" + "Log Message: " + "</strong>" + match[2] +
                        "<br/>" + "<hr>" + "<br/>";
                }
            }
            //Output the ERROR messages onto the HTML page
            document.getElementById("writeHere").innerHTML = outputToDisplay;
        }
    }

    else {
        $summary.text("There was a problem analyzing the errors or there are no errors in the log file!");
    }

    $showLog.text(res); // Prints AJAX response text onto html page
    console.timeEnd("Time locCat");
    console.timeEnd("Time DiaBtoa, reBSF, reRESP"); // Prints time of callback execution to console

};







