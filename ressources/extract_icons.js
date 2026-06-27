const fs = require('fs');
const path = require('path');

const svgPath = '/home/charles/Softwares/sfos/Trillium/harbour-trillium/ressources/logo.svg';
const outputDir = '/home/charles/Softwares/sfos/Trillium/harbour-trillium/qml/icons';

if (!fs.existsSync(outputDir)) {
    fs.mkdirSync(outputDir, { recursive: true });
}

console.log('Reading logo.svg...');
const content = fs.readFileSync(svgPath, 'utf8');

console.log('Parsing glyphs...');
const glyphTags = content.match(/<glyph\s+[^>]+>/g) || [];
console.log(`Found ${glyphTags.length} glyph tags.`);

let count = 0;
for (const tag of glyphTags) {
    const nameMatch = tag.match(/glyph-name="([^"]+)"/);
    const dMatch = tag.match(/\bd="([^"]+)"/);
    
    if (nameMatch && dMatch) {
        const glyphName = nameMatch[1];
        const pathData = dMatch[1];

        // Wrap the glyph path into a standard SVG file
        // We use scale(1, -1) and translate(0, -960) to convert the SVG Font coordinate system 
        // (origin at bottom-left, Y pointing up) to standard SVG (origin at top-left, Y pointing down).
        const svgContent = `<?xml version="1.0" encoding="utf-8"?>
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 1024 1024" width="24" height="24">
  <g transform="scale(1, -1) translate(0, -960)">
    <path d="${pathData}" fill="currentColor" />
  </g>
</svg>
`;

        fs.writeFileSync(path.join(outputDir, `${glyphName}.svg`), svgContent, 'utf8');
        count++;
    }
}

console.log(`Successfully extracted ${count} icons to ${outputDir}`);
