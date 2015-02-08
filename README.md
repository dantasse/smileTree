# smileTree
Smile into your webcam, and your computer will draw you a tree.

OpenFrameworks app, mashing together [ofxCv](https://github.com/kylemcdonald/ofxCv) and [ofxProcTree](https://github.com/mrbichel/ofxProcTree), which itself uses [ofxMeshUtils](https://github.com/ofZach/ofxMeshUtils). Thanks to Kyle McDonald, Johan Bichel Lindegaard, Ole Kristensen, and ofZach for creating these.

Here's what I did to get it running:

1. download OpenFrameworks (version 0.8.4 for osx/xcode)
2. clone or download this repo, put it in `of_v0.8.4_osx_release/apps/myApps`
3. download the required addons (ofxCv, ofxProcTree, ofxMeshUtils), unzip them, make sure their names are correct (e.g. ofxCv, not ofxCv-master), put the folders in `of_v0.8.4_osx_release/addons`. Note! The version of ofxCv you want is [0.8.4](https://github.com/kylemcdonald/ofxCv/releases/tag/0.8.4), as that plays well with ofx version 0.8.4.
4. open xcode, open the smileTree.xcodeproj file
5. pray to your deity or spirit of choice
6. try to run smileTree-debug
7. after nothing works, thrash around for the next 8 hours trying to get it to work.
8. oh, if xcode gives you a little ! warning thing and says to upgrade your project settings, don't do it. I'm not sure why.

If you can run it, it'll grab your webcam info and show you a little graph of how much it looks like you're smiling. If you smile enough for long enough, it'll draw you another tree. Smile longer and your tree will have more branches. A short smile will only give you a crummy little stick tree.
