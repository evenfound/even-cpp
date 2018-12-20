/** @brief Menu items */
var menuItem = {
    'Home<span class="sr-only">(current)</span>': {href: "/", title: "Нome"},
    'Nodes': {href: "/nodes.html", title: "Load all nodes list"},
    'Process': {href: "/process.html", title: "Process of simulayion"},
    'Ledger': {href: "/ledger.html", title: "Cloud IPFS transaction ledger"},
    'Network': {href: "/network.html", title: "Load network topology"},
};

/** @brief Draw menu */
function menu(active_) {
    var result = `<nav class="navbar navbar-expand-lg navbar-light bg-light mb-4">
            <a class="navbar-brand" href="/">EVEN boffin</a>
            <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNavAltMarkup" aria-controls="navbarNavAltMarkup" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbarNavAltMarkup">
                <div class="navbar-nav">`;
    $.each(menuItem, $.proxy(function (i, val) {
        var a = (i.includes(active_)) ? `active` : ``;
        result += `<a class="nav-item nav-link `
                + a
                + `" href="` + val.href + `" title="`
                + val.title + `">` + i + `</a>`;
    }, this));
    result += `</div>
            </div>
        </nav>`;
    document.write(result);
}
