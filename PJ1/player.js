function Player(){
    var Myself = this;
    this.config = function (Object) {
        Myself.playList = Object.playList;
        Myself.canvasId = Object.canvasId;
        Myself.handle = 0;
        load();
    }

    function load() {
        var audio = document.createElement("AUDIO");
        var player = document.getElementById("player");
        player.appendChild(audio);
        Myself.audio = audio;
        var playList = Myself.playList;
        Myself.audio.src = playList[0].mp3;
        var songInfo = document.getElementById('songInfo');
        var songTitle = document.createElement('div');
        songTitle.id = "songTitle";
        songInfo.appendChild(songTitle);
        var playerTime = document.getElementById("playerTime");
        Myself.playerTime = playerTime;
        var progress = document.getElementById("progress");
        progress.style.cursor = "pointer";        
        play();
    }

    function play(){
        Myself.audio.play();
        var playList = Myself.playList;
        var songTitle = document.getElementById("songTitle");
        songTitle.innerHTML = playList[0].title;
        songTitle.title = playList[0].title;
        timer = setInterval(function () {
            showTime();
        }, 1000);
        playHandle();    
    }

    function showTime() {
        if (Myself.audio.readyState == 4) {
            var duration = Myself.audio.duration;
            var currentTime = Myself.audio.currentTime;
            var ratio = ((currentTime / duration) * 100).toFixed(1);
            ratio = ratio == 100.0 ? 100 : ratio;
            function timeFormat(t) {
                return Math.floor(t / 60) + ":" + (t % 60 / 100).toFixed(2).slice(-2);
            }
            document.getElementById("playerProgressBar").style.width = ratio + "%";
            Myself.playerTime.innerHTML = timeFormat(currentTime) + "&nbsp;/&nbsp;" + timeFormat(duration) ;        
        } 
        else {
            Myself.playerTime.innerHTML = "-&nbsp;00:00&nbsp;/&nbsp;00:00&nbsp;";
        }
    }
    function playHandle() {
        var audioContext = new (window.AudioContext || window.webkitAudioContext)();
        var analyser = audioContext.createAnalyser();        
        var playData = audioContext.createMediaElementSource(Myself.audio);
        playData.connect(analyser);
        analyser.connect(audioContext.destination);
        analyser.fftSize = 256;
        bar(analyser);
    }


    function bar(analyser) {
        var canvas = document.getElementById(Myself.canvasId),
            meterWidth = 12, 
            capHeight = 2,
            meterNum = 1000 / (12 + 3), 
            ctx = canvas.getContext('2d'),
            capPosition = [],
            bars = Math.round(meterNum);
        var drawMeter = function () {
            var array = new Uint8Array(analyser.frequencyBinCount);
            analyser.getByteFrequencyData(array);
            var step = Math.round(array.length / meterNum); 
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            for (var i = 0; i < meterNum; i++) {
                var value = array[i * step];  
                if (capPosition.length < bars) {
                    capPosition.push(value); 
                };
                ctx.fillStyle = '#FFFFFF';
                if (value < capPosition[i]) {
                    ctx.fillRect(i * 15, canvas.height-2 - (--capPosition[i]), meterWidth, capHeight);
                } else {
                    ctx.fillRect(i * 15, canvas.height-2 - value, meterWidth, capHeight);
                    capPosition[i] = value;
                };
                ctx.fillStyle = '#258fb8';
                ctx.fillRect(i * 15, canvas.height - value, meterWidth, value);
            }
            requestAnimationFrame(drawMeter);
        }
        requestAnimationFrame(drawMeter);
    }

}