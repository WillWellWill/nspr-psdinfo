
var selectStat = function(id) {
    $("#statNavPort").removeClass("active");
    $("#statNavLive").removeClass("active");
    $("#statNavProtocol").removeClass("active");
    $("#statNavStream").removeClass("active");
    $(".stat-port-area").css("display", "none");
    $(".stat-live-area").css("display", "none");
    $(".stat-protocol-area").css("display", "none");
    $(".stat-stream-area").css("display", "none");
    $("#" + id).addClass("active");
    if (id == "statNavPort") {
        $(".stat-port-area").css("display", "block");
    }
    else if (id == "statNavLive") {
        $(".stat-live-area").css("display", "block");
    }
    else if (id == "statNavProtocol") {
        $(".stat-protocol-area").css("display", "block");
        InitStatisticsProtocol();
    }
    else if (id == "statNavStream") {
        $(".stat-stream-area").css("display", "block");
    }
};

var InitStatisticsProtocol = function() {
    var protocol = {};
    $("#stat-protocol").empty();
    protocol.time = "00:00:00";
    protocol.ip = "10.1.13.126";
    protocol.localPort = "1688";
    protocol.sid = "AB12-7896-B567-AB12-7896-B567-AB12-7896-B567-AB12-7896-B567";
    protocol.idx = 0;
    var item = StatisticsProtocol.constructItem(protocol);
    $("#stat-protocol").append(item);
    protocol.time = "00:00:01";
    protocol.ip = "10.1.13.126";
    protocol.localPort = "1688";
    protocol.sid = "CD4A-3EB8-DA64-034F-63CE-0A7F-E71C-94F4-DE5B-3CFD-7111-F7A0";
    protocol.idx = 1;
    item = StatisticsProtocol.constructItem(protocol);
    $("#stat-protocol").append(item);
};

var StatisticsProtocol = {
    constructItem : function(obj) {
        var content = "<div class='nspr-text protocol-item'>";
        content += "<span>start:" + obj.time + "</span>";
        content += "<span>from:" + obj.ip + "</span>";
        content += "<span>port:" + obj.localPort + "</span>";
        content += "<br/><span>" + obj.sid + "</span>";
        content += "<span class='message-toggle' id='msg-toggle-" + obj.idx + "' onclick='StatisticsProtocol.toggleMessage(" + obj.idx + ")'>Message+</span>";
        content += "</div>";
        content += "<div class='nspr-text protocol-item protocol-message' id='prot-msg-" + obj.idx + "'><span>AAAAA</span></div>";
        return content;
    },
    toggleMessage : function(idx) {
        if ($("#prot-msg-" + idx).css("display") == "none") {
            $("#prot-msg-" + idx).css("display", "block");
            $("#msg-toggle-" + idx).text("Message-");
        }
        else {
            $("#prot-msg-" + idx).css("display", "none");
            $("#msg-toggle-" + idx).text("Message+");
        }
    }
};

var ApiProcNetwork = {
	sendRequest : function(request, responseCB) {
		var xhr = new XMLHttpRequest();
		xhr.onreadystatechange = function() {
			if (xhr.readyState == 4) {
				if ((this.status >= 200 && this.status < 300) || this.status == 304) {
					console.log(this.responseText);
					var fixedResponse = this.responseText.replace(/\\'/g, "'");
					responseCB(fixedResponse, PortMgmt.portDesc);
					return;
				}
			}
		};
		xhr.open("get", request, true);
		xhr.send();
		console.log("send request");
	}
};

