#ifndef EXEC_2_HPP_INCLUDED
#define EXEC_2_HPP_INCLUDED

#pragma once

#include <string>
#include <assert.h>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <cstdlib>

using namespace std;

enum PIPE_FILE_DESCRIPTERS
{
  READ_FD  = 0,
  WRITE_FD = 1
};

enum CONSTANTS
{
  BUFFER_SIZE = 100
};

string exec_2(const vector<string> &command)
{
  int       parentToChild[2];
  int       childToParent[2];
  pid_t     pid;
  string    dataReadFromChild;
  char      buffer[BUFFER_SIZE + 1];
  ssize_t   readResult;
  int       status;

  assert(0 == pipe(parentToChild));
  assert(0 == pipe(childToParent));

  switch (pid = fork())
  {
    case -1:
      cerr << "Fork failed";
      exit(-1);

    case 0: /* Child */
      assert(-1 != dup2(parentToChild[READ_FD], STDIN_FILENO));
      assert(-1 != dup2(childToParent[WRITE_FD], STDOUT_FILENO));
      assert(-1!= dup2(childToParent[WRITE_FD], STDERR_FILENO));
      assert(0 == close(parentToChild [WRITE_FD]));
      assert(0 == close(childToParent [READ_FD]));

      /*     file, arg0, arg1,  arg2 */
      execlp(command[0].c_str(), command[0].c_str(), command[1].c_str(), command[2].c_str());

      cerr << "This line should never be reached!!!";
      exit(-1);

    default: /* Parent */
      cout << "Child " << pid << " process running..." << endl;

      assert(0 == close(parentToChild [READ_FD]));
      assert(0 == close(childToParent [WRITE_FD]));

      while (true)
      {
        switch (readResult = read(childToParent[READ_FD],
                                  buffer, BUFFER_SIZE))
        {
          case 0: /* End-of-File, or non-blocking read. */

            cout << "***End of file reached..."         << endl
                 << "Data received was ("
                 << dataReadFromChild.size() << "): " << endl
                 << dataReadFromChild                << endl;

            assert(pid == waitpid(pid, & status, 0));

            cout << endl
                 << "Child exit staus is:  " << WEXITSTATUS(status) << endl
                 << endl;

            exit(0);


          case -1:
            if ((errno == EINTR) || (errno == EAGAIN))
            {
              errno = 0;
              break;
            }
            else
            {
              cerr << "read() failed";
              exit(-1);
            }

          default:
            dataReadFromChild . append(buffer, readResult);
            break;
        }
      } /* while (true) */
  } /* switch (pid = fork())*/
    return dataReadFromChild;
}


#endif // EXEC_2_HPP_INCLUDED
