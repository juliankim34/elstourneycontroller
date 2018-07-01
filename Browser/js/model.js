$.fn.extend({
    animateCss: function(animationName, callback) {
        var animationEnd = (function(el) {
        var animations = {
                animation: 'animationend',
                OAnimation: 'oAnimationEnd',
                MozAnimation: 'mozAnimationEnd',
                WebkitAnimation: 'webkitAnimationEnd',
    };

    for (var t in animations) {
        if (el.style[t] !== undefined) {
            return animations[t];
         }
    }
})(document.createElement('div'));

this.addClass('animated ' + animationName).one(animationEnd, function() {
    $(this).removeClass('animated ' + animationName);

    if (typeof callback === 'function') callback();
    });

return this;
},    
});

function changeText(p1_text, p1_score_text, p2_text, p2_score_text) {
    // animate only if the text is changed
    if (p1_text != document.getElementById("p1").innerHTML) {
        $('#p1').animateCss("fadeOut", function() {
            document.getElementById("p1").innerHTML = p1_text;
            $('#p1').animateCss('fadeIn');
    });
    }
    if (p1_score_text != document.getElementById("p1_score").innerHTML) {
        $('#p1_score').animateCss("fadeOut", function() {
            document.getElementById("p1_score").innerHTML = p1_score_text;
            $('#p1_score').animateCss('fadeIn');
    });
    }
    if (p2_text != document.getElementById("p2").innerHTML) {
        $('#p2').animateCss("fadeOut", function() {
            document.getElementById("p2").innerHTML = p2_text;
            $('#p2').animateCss('fadeIn');
    });
    }
    if (p2_score_text != document.getElementById("p2_score").innerHTML) {
        $('#p2_score').animateCss("fadeOut", function() {
            document.getElementById("p2_score").innerHTML = p2_score_text;
            $('#p2_score').animateCss('fadeIn');
    });
    }
};

function readUpdates(xml) {
    var xmlDoc = xml.responseXML;
    //var x = xmlDoc.getElementsByTagName("updateNeeded");
    //var updateNeeded = x[0].childNodes[0].nodeValue;
    //document.getElementById("demo").innerHTML = updateNeeded;
    
    var p1 = xmlDoc.getElementsByTagName("p1")[0].childNodes[0].nodeValue;
    var p1_score = xmlDoc.getElementsByTagName("p1_score")[0].childNodes[0].nodeValue;
    var p2 = xmlDoc.getElementsByTagName("p2")[0].childNodes[0].nodeValue;
    var p2_score = xmlDoc.getElementsByTagName("p2_score")[0].childNodes[0].nodeValue;
    changeText(p1, p1_score, p2, p2_score);
};

function checkUpdates() {
    var xhttp = new XMLHttpRequest();
    xhttp.onload = function() {
        readUpdates(this);
    }
    xhttp.open("GET", "player_info.xml");
    xhttp.send();
};

function startChecks() {
    checkUpdates();
    setTimeout(startChecks, 3000);
};