var app = angular.module('devScreenApp', ['ngRoute']);

// Router for the SPA.
// Maps trailing URL fragment to the appropriate HTML template and Angular controller.
app.config(function($routeProvider) {
    $routeProvider
        .when('/', {
            templateUrl : 'tpl/home.html',
            controller  : 'mainController'
        })
        .when('/one', {
            templateUrl : 'tpl/one.html',
            controller  : 'oneController'
        })
        .when('/two', {
            templateUrl : 'tpl/two.html',
            controller  : 'twoController'
        });
});

// The home page controller. It does nothing.
app.controller('mainController', function($scope) {
    
});

// Controller for project #1.
app.controller('oneController', function($scope) {
    $scope.display = null;

    // This function gets called when the 'upload image' button is clicked.
    // It triggers the hidden file chooser on the page.
    $scope.chooseFile = function() {
        $('#fileChooser').trigger('click');
    };

    // Resets the image transformation options to their defaults and applies them.
    $scope.resetActions = function() {
        $('#scale')[0].value = '1.0';
        $('#rotate')[0].value = '0.0';
        $('#translatex')[0].value = '0.0';
        $('#translatey')[0].value = '0.0';
        $('#opacity')[0].value = '1.0';
        this.applyActions();
    };

    // Applies all of the image transformations.
    $scope.applyActions = function() {
        
        // Gets the transformation values from the page.
        // Could be improved with better checks on the user input.
        var ratio = parseFloat($('#scale')[0].value);
        var degree = parseFloat($('#rotate')[0].value);
        var tx = parseFloat($('#translatex')[0].value);
        var ty = parseFloat($('#translatey')[0].value);
        var alpha = parseFloat($('#opacity')[0].value);

        // Creates an HTML5 canvas and sets its size.
        var image = display;
        var canvas = $('#canvas')[0];
        canvas.width = canvas.scrollWidth;
        canvas.height = (image.height * ratio);

        // Clears the current display on the canvas.
        var ctx = canvas.getContext('2d');
        ctx.clearRect(0, 0, canvas.width, canvas.height);

        // Applies each of the transforms (except scaling).
        // Note that translation centers the image by default.
        ctx.globalAlpha = alpha;
        tx = tx + ((canvas.width - (image.width * ratio)) / 2.0);
        ctx.translate(tx, ty);
        if (degree != 0) {
            var hx = (image.width * ratio)/2;
            var hy = (image.height * ratio)/2;
            ctx.translate(hx, hy);
            ctx.rotate(degree*Math.PI/180);
            ctx.translate(-hx, -hy);
        }

        // Draws the image (scaling is applied here).
        ctx.drawImage(image, 0, 0, image.width, image.height, 0, 0, image.width * ratio, image.height * ratio); 
    };

    // Validates the file type of file it is passed, verifying that it is an image.
    $scope.validateImage = function(file) {

        // Uses a regex to determine that the file is an acceptable image type.
        var fileTypes = /(image\/jpg|image\/jpeg|image\/bmp|image\/gif|image\/png)$/i;
        if (fileTypes.test(file.type)){
            return true;
        }
        else {
            return false;
        }
    };

    // Takes in a picture file and displays it.
    $scope.readImage = function(pictureFile) {

        // Uses a file reader to get the image.
        // A callback is used to display the image by calling resetActions() once the image has loaded.
        var self = this;
        var reader = new FileReader();
        reader.onload = function(event) {
            var image = new Image();
            image.src = reader.result;
            image.onload = function () {
                display = image;
                self.resetActions();
            };
        };
        reader.readAsDataURL(pictureFile);
    };

    // Takes a file selected by a file chooser, validates that is an image and then displays it.
    $scope.selectImage = function(chooser) {
        var file = chooser.files[0];

        // If validation passes, we pass on the file to readImage() for processing and displaying.
        if (this.validateImage(file)) {
            this.readImage(file);
        }
    };

    // Reapplies the actions as the window is resized.
    // This is necessary because of the responsive bootstrap elements.
    $(window).bind('resize', function () {
        $scope.applyActions();
    });
});

// Controller for project #2.
app.controller('twoController', function($scope) {
    $scope.data = {};

    // Simply sends a get request to the server and displays the result.
    $scope.weatherReq = function() {
        $.get('api/weather', function(result) {
            $scope.data = result;
            $scope.$apply();
        })
    }
});