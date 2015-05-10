# fdimail
Mail manager modeled used OOP and General Programming procedures.

Roughly divided in two core programs.
Manager is the frontend. It operates a database in the form of template-instantiated inherited dynamic lists (now that was a mouthful). That is, there's a template class, List, which provides a base for the actual lists, mailList and userList. Now, each user has two trayLists and a contactList, which even if they are not enterely like the main ones, are similar enough to justify heredating them from the same template class, with the proper overrides.

Session and GraphInter constitue the client-side. Though in the beginning GraphInter was a pure I/O class, it evolved to handle mail creation logic. Not a really clean solution, but a functional one.

[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/Jsevillamol/fdimail?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
