import * as THREE from 'three';
import WebGL from 'three/addons/capabilities/WebGL.js';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera( 50, window.innerWidth / window.innerHeight, 1, 500 );
camera.position.set(0,0,60);
camera.lookAt(0,0,0);

const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );
const geometry = new THREE.BoxGeometry( 1, 1, 1 );
const material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
const cube = new THREE.Mesh( geometry, material );
const geometry2 = new THREE.CircleGeometry(1);
const circle = new THREE.Mesh(geometry2,material);
circle.position.x = -15;
cube.position.x = 15;

scene.add(cube,circle);


camera.position.z = 10;
renderer.render(scene,camera);


	function animate() {
        requestAnimationFrame( animate );
        if(cube.position.x > -15){
        cube.position.x -= 0.04;
        circle.position.x += 0.04;}

    
        renderer.render( scene, camera );
        }
    
    animate();
