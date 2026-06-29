# Trillium for Sailfish OS

A native **Trilium Next** (and Trilium Notes) client built specifically for Sailfish OS using Qt/QML and Silica UI components.

## About

Trillium allows you to connect to your self-hosted Trilium Next server, giving you seamless access to your hierarchical note-taking knowledge base directly from your mobile device.

## Supported Features

- **Login:** Stored using Sailfish secrets.
- **Hierarchical Note Browsing:** Seamlessly navigate through your note tree starting from your root notes. Supports visual type recognition and custom icon rendering (`text`, `code`, `image`, and binary attachments).
- **Rich Text & Code Viewing:** Read rich text notes and code snippets formatted to blend natively with the Sailfish OS dark/light Silica theme, complete with dynamically rendered embedded images.
- **Note Creation & Editing:**
  - Create new child notes inside any existing folder or parent note.
  - Edit rich text and code notes using a dedicated formatting toolbar supporting **Bold**, *Italic*, Underline, Headings (H1, H2, H3), plain text formatting, and inserting local images from your device gallery.
- **File & Image Downloads:** Easily download binary file notes and images directly to your device storage.
- **Notes icons:** Notes are displayed using their respective icons.

## Navigation

The app embraces native Sailfish OS navigation paradigms for an intuitive experience:

- **Sweep Navigation:** Swipe right to see subnotes, Swipe right to come back to parent node.
- **Note Overview (List View):**
  - **Tap the Note Icon (Left):** Navigates deeper into the note's hierarchy, displaying its sub-notes (children).
  - **Tap the Note Title (Right):** Opens the **Note Detail Page** to view the contents of the note.
  - **Long Press (Context Menu):** Press and hold on any note item to reveal options to *Open Sub-notes*, *View Details*, or *Delete* the note.
  - **Pull-Down Menu:** Pull down from the top of the list to *Add Note* in the current folder, *Refresh* notes, or *Disconnect* your session.
- **Note Detail Page:** Displays the note's content or download controls. Access the pull-down menu to *Edit* the note or *Refresh Content*.

## Development Notice

*This application was developed with the help of AI.

## License

TODO (BSD-3)
