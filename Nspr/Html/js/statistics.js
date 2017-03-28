
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
        InitStatisticsPort();
    }
    else if (id == "statNavLive") {
        $(".stat-live-area").css("display", "block");
        InitStatisticsLive();
    }
    else if (id == "statNavProtocol") {
        $(".stat-protocol-area").css("display", "block");
        InitStatisticsProtocol();
    }
    else if (id == "statNavStream") {
        $(".stat-stream-area").css("display", "block");
        InitStreamProtocol();
    }
};

var InitStatisticsProtocol = function() {
    var protocol = {};
    ApiDispatchNetwork.sendRequest("/api/statistics/query", StatisticsProtocol.onResponse);
};
var InitStatisticsPort = function() {
    var protocol = {};
    ApiDispatchNetwork.sendRequest("/api/statistics/query", StatisticsPort.onResponse);
};
var InitStatisticsLive = function() {
    var protocol = {};
    ApiDispatchNetwork.sendRequest("/api/statistics/query", StatisticsLive.onResponse);
};
var InitStatisticsStream = function() {
}

var StatisticsProtocol = {
    constructItem : function(obj) {
        var content =   
                "<div class='nspr-text protocol-item'>"+
                "  <span>start:@time</span>"+
                "  <span>from:@ip</span>"+
                "  <span>port:@localPort</span>"+
                "  <br/><span>@sid</span>"+
                "  <span class='message-toggle' id='msg-toggle-@idx' onclick='StatisticsProtocol.toggleMessage(@idx)'>Message+</span>"+
                "</div>"+
                "<div id='prot-msg-@idx' class='nspr-text protocol-message'>"+
                "  <div class='recv-message'>"+
                "    @recvmsg"+
                "  </div>"+
                "  <div class='send-message'>"+
                "    @sendmsg"+
                "  </div>"+
                "</div>";
        console.log(content);
        content = content.replace(/@time/g, obj.starttime);
        content = content.replace(/@ip/g, obj.ip);
        content = content.replace(/@localPort/g, obj.port);
        content = content.replace(/@sid/g, obj.sid);
        content = content.replace(/@idx/g, obj.idx);

        var recvmsg = "";
        for (idx in obj.recvmsg) {
            var msg = obj.recvmsg[idx];
            msg = msg.replace(/@newline/g, "</span><br/><span>");
            msg = "<span>" + msg + "</span><br/>";
            recvmsg += msg;
        }
        content = content.replace(/@recvmsg/g, recvmsg);
        var sendmsg = "";
        for (idx in obj.sendmsg) {
            var msg = obj.sendmsg[idx];
            msg = msg.replace(/@newline/g, "</span><br/><span>");
            msg = "<span>" + msg + "</span><br/>";
            sendmsg += msg;
        }
        content = content.replace(/@sendmsg/g, sendmsg);
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
    },
    onResponse : function(response) {
        var obj = JSON.parse(response);
        if (!obj['status'] || obj['status'] != 'ok') {
            console.log("status of statistics not ok");
            return;
        }
        $("#stat-protocol").empty();
        
        if (!obj.statistics) {
            console.log("statistics not ready");
            return;
        }

        for (idx in obj.statistics) {
            if (obj.statistics[idx].type == "protocol") {
                StatisticsProtocol.handleProtocol(obj.statistics[idx], idx);
            }
        }
    },
    handleProtocol : function(protocol, idx) {
        protocol.idx = idx;
        console.log(idx);
        var item = StatisticsProtocol.constructItem(protocol);
        $("#stat-protocol").append(item);
    }
};

var StatisticsPort = {
    constructItem : function(obj) {
        var content =   
                "<div class='nspr-text protocol-item'>"+
                "  <span>start:@time</span>"+
                "  <span>virtualport:@virtualport</span>"+
                "  <span>agent:@isagent</span>"+
                "  <br/><span>videoport:@videoport</span>"+
                "  <span>audioport:@audioport</span>"+
                "  <br/><span>liveid:@liveid</span>"+
                "</div>";
        console.log(content);
        content = content.replace(/@time/g, obj.starttime);
        content = content.replace(/@virtualport/g, obj.virtualport);
        content = content.replace(/@isagent/g, obj.isagent ? "true" : "false");
        content = content.replace(/@videoport/g, obj.videoport);
        content = content.replace(/@audioport/g, obj.audioport);
        content = content.replace(/@liveid/g, obj.liveid);

        return content;
    },
    onResponse : function(response) {
        var obj = JSON.parse(response);
        if (!obj['status'] || obj['status'] != 'ok') {
            console.log("status of statistics not ok");
            return;
        }
        $("#stat-port").empty();
        
        if (!obj.statistics) {
            console.log("statistics not ready");
            return;
        }

        for (idx in obj.statistics) {
            if (obj.statistics[idx].type == "port") {
                StatisticsPort.handlePort(obj.statistics[idx], idx);
            }
        }
    },
    handlePort : function(port, idx) {
        var item = StatisticsPort.constructItem(port);
        $("#stat-port").append(item);
    }
};

var StatisticsLive = {
    constructItem : function(obj) {
        var content =   
                "<div class='nspr-text protocol-item'>"+
                "  <span>start:@time</span>"+
                "  <span>liveid:@liveid</span>"+
                "  <span>virtualport:@virtualport</span>"+
                "  <br/><span>sid:@sid</span>"+
                "</div>";
        console.log(content);
        content = content.replace(/@time/g, obj.starttime);
        content = content.replace(/@liveid/g, obj.liveid);
        content = content.replace(/@virtualport/g, obj.virtualport);
        content = content.replace(/@sid/g, obj.sid);

        return content;
    },
    onResponse : function(response) {
        var obj = JSON.parse(response);
        if (!obj['status'] || obj['status'] != 'ok') {
            console.log("status of statistics not ok");
            return;
        }
        $("#stat-live").empty();
        
        if (!obj.statistics) {
            console.log("statistics not ready");
            return;
        }

        for (idx in obj.statistics) {
            if (obj.statistics[idx].type == "live") {
                StatisticsLive.handleLive(obj.statistics[idx], idx);
            }
        }
    },
    handleLive : function(live, idx) {
        var item = StatisticsLive.constructItem(live);
        $("#stat-live").append(item);
    }
};

var ApiDispatchNetwork = {
	sendRequest : function(request, responseCB) {
		var xhr = new XMLHttpRequest();
		xhr.onreadystatechange = function() {
			if (xhr.readyState == 4) {
				if ((this.status >= 200 && this.status < 300) || this.status == 304) {
					//console.log(this.responseText);
					var fixedResponse = this.responseText.replace(/\\'/g, "'");
					fixedResponse = fixedResponse.replace(/\r/g, "");
					fixedResponse = fixedResponse.replace(/\n/g, "@newline");
					responseCB(fixedResponse);
					return;
				}
			}
		};
		xhr.open("get", request, true);
		xhr.send();
		console.log("send request");
	}
};

