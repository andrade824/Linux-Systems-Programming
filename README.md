Linux Systems Programming
=========================

This repository contains projects I've created to help me master systems programming on linux.

The two projects I've created so far:
<ul>
    <li><strong>Server based calculator:</strong> Using both sockets and child processes I've created a client-server calculator of sorts. Essentially, you run the "Client" on one computer/terminal, and the "Server" on another. On the client, you can input mathematical expressions (like "2+2"), the expression will be sent to the server via sockets, the expression will be processed, then the result will be sent back to the client for viewing.</li>
    <li><strong>Threads Example: This is just some example code for working with threads. It shows the basics needed to make multithreaded applications on linux (creating and starting threads, and killing/waiting for them to complete. </li>
</ul>

To build any of the projects in this repository, just run "make" in the project's directory. To run the server based calculator project, run the "Server" executable on one computer/terminal, and in another computer/terminal run "./Client [yourcomputernamehere]".
