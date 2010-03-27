		<cfif NOT fileExists(arguments.path)>
			<cfthrow
				type="Alagad.Image.InvalidPath"
				message="Invalid path argument.  The path specified does not exist or is not accessible. (#arguments.path#)  Please provide a valid path to an image file." />
		</cfif>