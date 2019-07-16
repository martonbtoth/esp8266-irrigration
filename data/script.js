(function () {
    var button = document.querySelector("#button");
    var state = null;
    
    function refresh() {
        fetch("/status").then(function(response) {
            return response.text();
        }).then(function (text) {
            state = text;
            document.querySelector("#status").textContent = state;
            if (state === 'on') {
                button.textContent = "Turn off"
            } else {
                button.textContent = "Turn on"
            }
        });
    }

    button.addEventListener('click', function () {
        if (state === 'on') {
            fetch('/off', {method: 'post'}).then(refresh);
        } else {
            fetch('/on', {method: 'post'}).then(refresh);
        }
    });
    
    refresh();
    
})()
