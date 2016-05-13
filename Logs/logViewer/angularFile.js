/*
* Created by Johan Oakes on 6/2/2014.
*
* Log Parsing Tool used to analyze log files on HP Anywhere servers.
*
*/


var app = angular.module('logPars', []);

/*
* controller to display the content area of the file read
* passing an array -> protects against minification
* $ calls the built in Angular services
*/
app.controller('logFileCTRL', ['$scope', function (a) {
  a.showContent = function (content) {
    a.content = content;
  };
}]);

app.directive('onReadFile', function ($parse) {

  return {

    // When creating a directive. it is restricted to attribute by default
    //restrict: 'A', used when when decorating an existing element with new functionality
    scope: {
      // & sign lets you invoke an expression on the parent scope ($scope.showContent)
      onReadFile: "&"
    },

    /*
    * Directives that want to modify the DOM use the link option
    * scope -> Angular scope object
    * element -> jQLite wrapped element that this directive matches
    * attrs -> hash object with key-value pairs of normalized attribute names
    *          and their corresponding attribute values
    */
    link: function (scope, element, attrs) {

      //Binds to the element click event
      element.on('change', function (e) {

        document.getElementById("writeHere").innerText = "Reading...";

        var reader = new FileReader();

        //Reads the file
        reader.readAsText((e.srcElement || e.target).files[0]);

        // After obtaining a File reference, instantiate a FileReader object to read its contents
        // into memory. When the load finished, reader's onload event is fired and its result attr
        // can be used to access the file data
        reader.onload = function (e) {

          scope.$apply(function () {

            analyzeLog(reader);

            // Prints the log file to the DOM
            document.getElementById("showLog").innerHTML = reader.result;

          });
        };

        // Handle error when log file fails to load
        reader.onerror = function (e) {
          alert("Could not load log file!");
        };

        // If we use onloadend, we need to check the readyState.
        reader.onloadend = function (evt) {
          if (evt.target.readyState == FileReader.DONE) { // DONE == 2
            console.log("File has been read successfully!");
          }
        };
      });
    }
  };
});

/*
* Use to read through the log file, extract the number of errors,
* prompt the user for requested number of errors, and output the errors
* onto the DOM
*/
var analyzeLog = function (reader) {

  // Used to put the file into an array by lines, so I can reverse it and get the N most recent erros
  var array = reader.result.toString().split('\n');
  var newArray = array.reverse();

  // Matches the log file messages with the regex (re) to extract all the summaries


  var outputToDisplay = " "; // Outputs the errors to the html page

  var num = prompt("What messages do you want to see?");

  // Regex Lines
  var logs = //;
  // TODO : Include OS regex
  var browser = /((?<=")[a-zA-Z]+\/[0-9]+\.[0-9]+)/g;
  var ip = /(^(?:[0-9]{1,3}\.){3}[0-9]{1,3})/gm;
  var date_time = /(\[[0-9]{2}\/[a-zA-Z]{3,}\/[0-9]{4}(?:\:[0-9]{2}){3} \+[0-9]{4}\])/g;
  var file = /((?<= \/)[a-zA-Z0-9]+\.[a-z]+)/g;
  var referrer = /((?<=\")[a-z]{4,5}\:\/\/(?:.+?).[a-z]+(?=\"))/g;
  var log_ex = "127.0.0.1 - - [19/Jun/2012:09:16:22 +0100] \"GET /GO.gif HTTP/1.1\" 499 0 \"http://domain.com/htm_data/7/1206/758536.html\" \"Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Trident/4.0; .NET CLR 1.1.4322; .NET CLR 2.0.50727; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; SE 2.X MetaSr 1.0)\"";


  if (logs.test(reader.result)) {
    for (var j = 0, k = newArray.length; j <= k; j++) { // Since newArray[0] contains an empty string

      while ((match = reDiaBtoa.exec(newArray[j])) != null) {

        if (match.index === reDiaBtoa.lastIndex) {
          reDiaBtoa.lastIndex++;
        }

        if (match[2] === "ERROR" && errCount < num) {

          errCount++;

          // Summary of the ERROR log messages
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

  else {
    document.getElementById("writeHere").innerHTML = "There was a problem analyzing the errors or there does not exist any errors in the log file.";
  }
};
