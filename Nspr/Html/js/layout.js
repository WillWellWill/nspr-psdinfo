
function openNav() {
    $("#mySidenav").css("width", "12%");
}

function closeNav() {
    $("#mySidenav").css("width", "0");
}

function hideAllContainer() {
    $(".statistics-container").css("display", "none");
    $(".diagram-container").css("display", "none");
    $(".logviewer-container").css("display", "none");
    $(".settings-container").css("display", "none");
}

var currentId = 'navStart';
function selectContainer(id) {
    if (currentId == id) {
        closeNav();
        return;
    }

    hideAllContainer();
    if (id == 'navStatistics') {
        $(".statistics-container").css("display", "block");
    }
    else if (id == 'navDiagram') {
        $(".diagram-container").css("display", "block");
    }
    else if (id == 'navLogViewer') {
        $(".logviewer-container").css("display", "block");
    }
    else if (id == 'navSettings') {
        $(".settings-container").css("display", "block");
    }
    currentId = id;
    closeNav();
}


