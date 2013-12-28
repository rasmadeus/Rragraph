import QtQuick 2.0
import QtQuick.Particles 2.0
import "../"

ContentBackground{
    mainColor: "#ff0"
    ParticleSystem{
        anchors.fill: parent
        Emitter{
            width: parent.width
            emitRate: 4
            lifeSpan: 14000
            size: 80
            velocity: PointDirection { y: 60 }
        }
        Wander{
            anchors.fill: parent
            anchors.bottomMargin: 100
            xVariance: 60
            pace: 60
        }
        Affector{
            property real coefficient: 0.1
            property real velocity: 1.5
            width: parent.width
            height: parent.height - 100
            onAffectParticles: {
                for (var i=0; i<particles.length; i++) {
                    var particle = particles[i];
                    if (particle.r === 0.0) {
                        particle.r = Math.random() + 0.01;
                    }
                    particle.rotation += velocity * particle.r * dt;
                    particle.r -= particle.rotation * coefficient;
                    if (particle.r === 0.0)
                        particle.r -= particle.rotation * 0.000001;
                    particle.update = 1;
                }
            }
        }
        Affector{
            x: -60
            width: parent.width + 120
            height: 100
            anchors.bottom: parent.bottom
            onAffectParticles: {
                for (var i=0; i<particles.length; i++) {
                    var particle = particles[i];
                    var pseudoRand = (Math.floor(particle.t*1327) % 10) + 1;
                    var yslow = dt * pseudoRand * 0.5 + 1;
                    var xslow = dt * pseudoRand * 0.05 + 1;
                    if (particle.vy < 1)
                        particle.vy = 0;
                    else
                        particle.vy = (particle.vy / yslow);
                    if (particle.vx < 1)
                        particle.vx = 0;
                    else
                        particle.vx = (particle.vx / xslow);
                    particle.update = true;
                }
            }
        }
        ImageParticle{
            anchors.fill: parent
            id: particles
            z:4
            sprites: [
                Sprite {
                    source: "qrc:/res/help/realLeaf1.png"
                    frameCount: 1
                    frameDuration: 1
                    to: {"a":1, "b":1, "c":1, "d":1}
                },
                Sprite {
                    name: "a"
                    source: "qrc:/res/help/realLeaf1.png"
                    frameCount: 1
                    frameDuration: 10000
                },
                Sprite {
                    name: "b"
                    source: "qrc:/res/help/realLeaf2.png"
                    frameCount: 1
                    frameDuration: 10000
                },
                Sprite {
                    name: "c"
                    source: "qrc:/res/help/realLeaf3.png"
                    frameCount: 1
                    frameDuration: 10000
                },
                Sprite {
                    name: "d"
                    source: "qrc:/res/help/realLeaf4.png"
                    frameCount: 1
                    frameDuration: 10000
                }
            ]
        }
    }
}
