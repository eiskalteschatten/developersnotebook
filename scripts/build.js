'use strict';

const path = require('path');
const compileSass = require('compile-sass');

const cssConfig = require('../config/css');


module.exports = async () => {
    console.log('Compiling SCSS files...');

    await compileSass.compileSassAndSaveMultiple({
        sassPath: path.join('./src/', '/scss/'),
        cssPath: path.join('./resources/', '/css/'),
        files: cssConfig.sassFilesToCompile
    });

    console.log('Finished compiling SCSS files.');
};
